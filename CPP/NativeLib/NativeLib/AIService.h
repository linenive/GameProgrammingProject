#pragma once
#include "Character.h"
#include "TaskReserveInfo.h"
#include "AIExecuter.h"
#include "TaskService.h"
#include "CoordinatesSystem.h"
#include "Timer.h"
#include "GameRule.h"
#include "ItemDictionary.h"

class AIService {

private:
	ObjectService* object_service;
	TaskService* task_service;
	StaticUnitService* static_unit_service;
	ResidentService* resident_service;
	AIExecuter ai_executer;

	list<pair<int, Task*>> task_list; 

	Timer task_assign_timer;
	Timer task_execute_timer;

	void ReserveWorldObject(WorldObject target, TaskReserveInfo task_reserve_info);

	bool HasEnoughItem(Resident* resident) {
		return resident->GetInventory()->GetItemCount(Coordinates(0, 0)) >= 10;
	}

	bool HasSamePosition(Resident* resident, Vector2 target_pos) {
		return AbsolutePositionToCoordinates(resident->GetPhysics()->GetPosition())
			== AbsolutePositionToCoordinates(target_pos);
	}

	bool HasInventoryStructureInHome(Resident* resident) { //To-do home -> work_space
		Building* home = static_unit_service->GetBuildingById(resident->home_id);
		for (auto id : home->inside_structures_list) {
			Structure* inside_structure = static_unit_service->GetStructureById(id);
			if (inside_structure->HasInventory())
				return true;
		}
		return false;
	}

	void MoveCharacterItemToOtherInventory(Resident* resident, Item item, Inventory* other_inventory) {
		Inventory* char_inventory = resident->GetInventory();
		int amount = char_inventory->GetItemCountByItemId(item.GetID());
		char_inventory->PopItemById(item.GetID(), amount);
		other_inventory->AddItem(item, amount);
	}

	Task* FindNewTaskToResident(Resident* resident) {
		if (resident->GetGender() == WOMAN && HasInventoryStructureInHome(resident)) {
			if (HasEnoughItem(resident)) {
				if (HasSamePosition(resident, resident_service->GetResidentHomePosition(resident->GetId()))) {
					MoveCharacterItemToOtherInventory(
						resident,
						*ItemDictionary::GetInstance()->GetItemByName("wood"),
						static_unit_service->GetFirstInventoryInBuildingById(resident->home_id)
					);
					return task_service->CreateWanderTask(resident); //temp
				}
				else {
					return task_service->CreateSeekTaskToHome(resident);
				}
			}
			else {
				Vector2 tree_pos = static_unit_service->GetNearestStructurePos(
					AbsolutePositionToCoordinates(resident->GetPhysics()->GetPosition()),
					eStructureType::TREE
				);

				if (HasSamePosition(resident, tree_pos)) {
					return task_service->CreateWorkTask(eWorkType::COLLECT_WOOD);
				}
				else {
					return task_service->CreateSeekTask(resident, tree_pos);
				}
			}
		}
		else {
			return task_service->CreateSeekTaskToHome(resident);
		}
	}
	// To-do: hard coding -> algorithm which use DB
	Task* FindNewTaskToGuest(Guest* performer) {
		vector<PurposeOfVisit*> purposes = ((GuestSchedule*)(performer->GetSchedule()))->GetPurposOfVisit();
		for (PurposeOfVisit* p : purposes) {
			if (p->CanExecute()) {
				// To-do: 
				return task_service->CreateWanderTask(performer);
			}
		}
		return task_service->CreateLeaveVillageTask(performer);
	}
	void AssignTaskToWholeCharacter() {
		// To-do: task allocator for task priority
		Character* performer;
		auto it = task_list.begin();
		while (it != task_list.end()) {
			performer = object_service->GetCharacter(it->first);
			if (performer == nullptr) {
				
				task_list.erase(it);
				
				continue;
			}
			// To-do: 우선순위 비교하여 변동 없을 시 무시하기.
			delete it->second;
			it->second = nullptr;
			if (performer->IsGuest())
				it->second = FindNewTaskToGuest((Guest*)performer);
			else
				it->second = FindNewTaskToResident((Resident*)performer);
			++it;
		}
	}
	void ExecuteCharactersTask(){
		Character* performer;
		auto it = task_list.begin();
		while (it != task_list.end()) {
			performer = object_service->GetCharacter(it->first);
			if (performer == nullptr) {
				it = task_list.erase(it);
				continue;
			}
			ai_executer.ExecuteCharacterTask(performer, it->second);
			++it;
		}
	}

	void DeleteLeavers() {
		queue<int>* village_leavers = &ai_executer.village_leavers;
		while (!village_leavers->empty()) {
			int id = village_leavers->front();
			village_leavers->pop();
			object_service->DeleteCharacter(id);
		}
	}

public:
	~AIService() {
		delete task_service;
	}
	AIService(ObjectService* _object_service, TaskService* _task_service, 
			StaticUnitService* _static_unit_service, ResidentService* _resident_service)
		: object_service(_object_service), task_service(_task_service), 
		static_unit_service(_static_unit_service), resident_service(_resident_service),
		task_assign_timer(Timer(ASSIGN_TASK_INTERVAL_TIME)), task_execute_timer(Timer(EXECUTE_TASK_INTERVAL_TIME)){
		map<int, Character*>* characters = object_service->GetCharacters();
		for (auto &kv : *characters) {
			task_list.push_back({ kv.first, nullptr});
		}
	}

	void AddNewCharacter(int id) {
		Character* new_character = object_service->GetCharacter(id);
		if(new_character->IsGuest())
			task_list.push_back({ id, FindNewTaskToGuest((Guest*)new_character)});
		else
			task_list.push_back({ id, FindNewTaskToResident((Resident*)new_character)});
	}

	void Update(float delta) {
		task_assign_timer.TimeGo(delta);
		int task_assign_number = task_assign_timer.GetPassNumberAndReset();
		while (task_assign_number > 0) {
			AssignTaskToWholeCharacter();
			task_assign_number--;
		}
		task_execute_timer.TimeGo(delta);
		int task_execute_number = task_execute_timer.GetPassNumberAndReset();
		while (task_execute_number > 0) {
			ExecuteCharactersTask();
			task_execute_number--;
		}
		
		DeleteLeavers();
	}
};