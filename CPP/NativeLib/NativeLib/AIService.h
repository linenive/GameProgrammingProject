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

	queue<Character*>* village_leavers;

	vector<Character*>* characters;
	vector<Character*>* guests;
	vector<Character*>* residents;
	AIExecuter* ai_executer;
	
	Timer task_assign_timer;
	/*
	void ChangeTaskTarget(Character* performer, Vector2 target) {
		TaskForMove* currentTask = dynamic_cast<TaskForMove*>(performer->GetSchedule()->GetTask());
		if (currentTask == nullptr) return;
		printf("ChangeTaskTarget2\n");
		currentTask->ChangeTarget(performer->GetPhysics().GetPosition(),target);
	}*/
	void ReserveWorldObject(WorldObject target, TaskReserveInfo task_reserve_info);
	void AddLeaveVillageTask(Character* character) {
		Vector2 leave_point = CoordinatesToCenterVector(character->GetSchedule()->GetVillageDeparturePoint());
		Task* new_task = task_service->CreateSeekTask(character, leave_point);
		character->GetSchedule()->SetTask(new_task);
	}
	void AddIdleTask(Character* performer) {
		// 미구현
	}
	void FindNewTaskToResident(Character* resident) {
		AddIdleTask(resident);
	}
	// To-do: hard coding -> algorithm which use DB
	void FindNewTaskToGuest(Character* guest) {
		vector<PurposeOfVisit*> purposes = ((GuestSchedule*)(guest->GetSchedule()))->GetPurposOfVisit();
		for (PurposeOfVisit* p : purposes) {
			if (p->CanExecute()) {
				// To-do: 
				AddIdleTask(guest);
				return;
			}
		}
		AddLeaveVillageTask(guest);
	}
	void AssignTaskToResidents() {
		// To-do: Task가 있어도 중요도에 따라 새로 할당하는 기능
		for (Character* c : *residents) {
			if (!c->GetSchedule()->HasTask())
				FindNewTaskToResident(c);
		}
	}
	void AssignTaskToGuests() {
		// To-do: Task가 있어도 중요도에 따라 새로 할당하는 기능
		for (Character* c : *guests) {
			if (!c->GetSchedule()->HasTask())
				FindNewTaskToGuest(c);
		}
	}
	void AssignTaskToWholeCharacter() {
		AssignTaskToResidents();
		AssignTaskToGuests();
	}
	void ExecuteCharactersTask() {
		for (Character* c : *characters) {
			ai_executer->ExecuteCharacterTask(c);
		}
	}

public:
	~AIService() {
		delete ai_executer;
		delete task_service;
	}
	AIService(ObjectService* _object_service, TaskService* _task_service)
		: object_service(_object_service), task_service(_task_service),
		task_assign_timer(Timer(ASSIGN_TASK_INTERVAL_TIME)) {
		characters = object_service->GetCharacters();
		guests = object_service->GetGuests();
		residents = object_service->GetResidents();
	}
	void Update(float delta) {
		task_assign_timer.timeGo(delta);
		if (task_assign_timer.isTimeEnd()) {
			AssignTaskToWholeCharacter();
			task_assign_timer.reset();
		}

		ExecuteCharactersTask();
	}

	queue<Character*>* GetVillageLeavers() {
		return village_leavers;
	}
};