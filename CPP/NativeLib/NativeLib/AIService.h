#pragma once
#include "Character.h"
#include "TaskReserveInfo.h"
#include "AIExecuter.h"
#include "TaskService.h"
#include "VillageService.h"
#include "CoordinatesSystem.h"
#include "Timer.h"
#include "GameRule.h"
#include "ItemDictionary.h"
#include "UIService.h"
#include "ObjectService.h"
#include "StaticUnitService.h"

class AIService {

private:
	UIService* ui_service;
	ObjectService* object_service;
	TaskService* task_service;
	StaticUnitService* static_unit_service;
	ResidentService* resident_service;
	VillageService* village_service;
	AIExecuter ai_executer;

	list<pair<int, Task*>> task_list; 

	Timer task_assign_timer;
	Timer task_execute_timer;

	void ReserveWorldObject(WorldObject target, TaskReserveInfo task_reserve_info);

	bool HasEnoughItem(Resident* resident) {
		return resident->GetInventory()->GetItemCount(Coordinates(0, 0)) >= 10;
	}

	bool HasSamePosition(Character* character, Vector2 target_pos) {
		return AbsolutePositionToCoordinates(character->GetPhysics()->GetPosition())
			== AbsolutePositionToCoordinates(target_pos);
	}

	bool HasInventoryStructureInWorkSpace(Resident* resident) { //To-do home -> work_space
		return static_unit_service->HasInventoryStructureInBuildingById(resident->work_space_id);
	}

	void MoveCharacterItemToOtherInventory(Resident* resident, Item item, Inventory* other_inventory) {
		Inventory* char_inventory = resident->GetInventory();
		int amount = char_inventory->GetItemCountByItemId(item.GetID());
		char_inventory->PopItemById(item.GetID(), amount);
		other_inventory->AddItem(item, amount);
	}

	Task* FindNewTaskToResident(Resident* resident) {
		if (resident->work_space_id != -1 && HasInventoryStructureInWorkSpace(resident)) {
			if (HasEnoughItem(resident)) {
				if (HasSamePosition(resident, resident_service->GetResidentWorkSpacePosition(resident->GetId()))) {
					int add_item_structure_id = static_unit_service->GetFirstStructureHasInventoryInBuildingById(resident->work_space_id)->id;
					MoveCharacterItemToOtherInventory(
						resident,
						*ItemDictionary::GetInstance()->GetItemByName("wood"),
						static_unit_service->GetFirstInventoryInBuildingById(resident->work_space_id)
					);
					ui_service->ui_update_needed_structure_ids.push(add_item_structure_id);
					return task_service->CreateSeekTaskToWorkSpace(resident); //temp
				}
				else {
					return task_service->CreateSeekTaskToWorkSpace(resident);
				}
			}
			else {
				Inventory* target_inventory = 
					static_unit_service->GetFirstInventoryInBuildingById(resident->work_space_id);
				if (target_inventory->GetItemCountByItemId(
					ItemDictionary::GetInstance()->GetIDByName("wood")) >= 5) {
					if (HasSamePosition(resident, resident_service->GetResidentWorkSpacePosition(resident->GetId()))) {
						return task_service->CreateWorkTask(eWorkType::CREATE_ITEM, target_inventory, 1);
					}
					return task_service->CreateSeekTaskToWorkSpace(resident);
				}

				Vector2 tree_pos = static_unit_service->GetNearestStructurePos(
					AbsolutePositionToCoordinates(resident->GetPhysics()->GetPosition()),
					eStructureType::TREE
				);

				if (HasSamePosition(resident, tree_pos)) {
					return task_service->CreateWorkTask(
						eWorkType::COLLECT_WOOD, resident->GetInventory(), 12
					);
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
			if (p->GetType() == ePurposeOfVisitType::BuyFirewood && !p->is_done) {
				Building* shop = static_unit_service->GetFirstShop();
				if (shop == nullptr) {
					continue;
				}
				if (HasSamePosition(performer, shop->GetCenterPosition())) {
					shop->IncreaseOneVisits();
					p->is_done = true;
					return task_service->CreateShoppingTask(
						shop, ItemDictionary::GetInstance()->GetIDByName("wood"));
				}
				else {
					return task_service->CreateSeekTask(performer, shop->GetCenterPosition());
				}
			}
			// return task_service->CreateWanderTask(performer);
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
				delete(it->second);
				it = task_list.erase(it);
				
				continue;
			}
			// To-do: �켱���� ���Ͽ� ���� ���� �� �����ϱ�.
			if (it->second != nullptr && it->second->IsTaskDone()) {
				delete it->second;
				it->second = nullptr;
			}
				
			if (it->second == nullptr) {
				if (performer->IsGuest()) {
					it->second = FindNewTaskToGuest((Guest*)performer);
				}
				else {
					it->second = FindNewTaskToResident((Resident*)performer);
				}
			}
			++it;
		}
	}

	// Task ���� �����ϱ⿣ �ð��� ��� ���⿡ �˰����� �־���.
	void ShoppingAlgorithm(Character* character, ShoppingTask* task) {
		if (task->IsShoppingEnd()) {
			task->Done();
			return;
		}

		Structure* target_structure = static_unit_service->GetStructureById(*task->structure_iterator);
		if (target_structure == nullptr) {
			task->structure_iterator++;
			return;
		}

		if (HasSamePosition(character, target_structure->GetCenterPosition())) {
			task->structure_iterator++;
			
			if (target_structure->HasInventory() && target_structure->GetInventory()->GetItemCountByItemId(task->wish_item_code) > 0) {
				Item* item = ItemDictionary::GetInstance()->GetItemByID(task->wish_item_code);
				target_structure->GetInventory()->PopItemById(task->wish_item_code, 1);
				ui_service->ui_update_needed_structure_ids.push(target_structure->id);
				int price = item->GetParameter("price");
				village_service->IncreaseMoney(price, character->GetPhysics()->GetPosition());
				character->GetInventory()->AddItem(*item, 1);
				ui_service->ui_update_needed_character_ids.push(character->GetId());
				task->Done();
			}
			return;
		}
		else {
			task_service->SetTaskPathTempFunc(task, character, target_structure->GetCenterPosition());
			task->NextAction();
			return;
		}

	}

	void ExecuteCharactersTask(){
		Character* performer;
		auto it = task_list.begin();
		while (it != task_list.end()) {
			performer = object_service->GetCharacter(it->first);
			if (performer == nullptr) {
				delete(it->second);
				it = task_list.erase(it);
				continue;
			}

			if (it->second->GetType() == eTaskType::SHOPPING) {
				ShoppingAlgorithm(performer, (ShoppingTask*)it->second);
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
			StaticUnitService* _static_unit_service, ResidentService* _resident_service,
			VillageService* _village_service, UIService* _ui_service)
		: object_service(_object_service), task_service(_task_service), 
		static_unit_service(_static_unit_service), resident_service(_resident_service),
		village_service(_village_service), ui_service(_ui_service),
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
	vector<int> GetTaskIDList() {
		vector<int> task_id_list;
		for (auto it : task_list) {
			task_id_list.push_back(it.first);
		}
		return task_id_list;
	}
	bool HasTaskByID(int id) {
		for (auto it : task_list) {
			if (it.first == id) {
				return true;
			}
		}
		return false;
	}
};