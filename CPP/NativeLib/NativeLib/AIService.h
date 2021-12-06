#pragma once
#include "Character.h"
#include "TaskReserveInfo.h"
#include "AIExecuter.h"
#include "TaskService.h"
#include "CoordinatesSystem.h"
#include "Timer.h"
#include "GameRule.h"

class AIService {

private:
	ObjectService* object_service;
	TaskService* task_service;
	AIExecuter ai_executer;

	list<pair<int, Task*>> task_list; 

	Timer task_assign_timer;
	Timer task_execute_timer;

	void ReserveWorldObject(WorldObject target, TaskReserveInfo task_reserve_info);

	Task* FindNewTaskToResident(Resident* resident) {
		return task_service->CreateSeekTaskToHome(resident);
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
	AIService(ObjectService* _object_service, TaskService* _task_service)
		: object_service(_object_service), task_service(_task_service),
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