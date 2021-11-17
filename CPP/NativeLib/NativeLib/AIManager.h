#pragma once
#include "Character.h"
#include "TaskReserveInfo.h"
#include "GameWorldForAI.h"
#include "AIExecuter.h"
#include "TaskForIdleMove.h"
#include "PathFinder.h"
#include "Task.h"
#include "CoordinatesSystem.h"
#include "Timer.h"
#include "GameRule.h"

class AIManager {

private:
	GameWorldForAI* game_world;
	vector<Character*>* characters;
	vector<Character*>* guests;
	vector<Character*>* residents;
	AIExecuter* ai_executer;
	TileRepository* now_tile_repo;
	Timer assign_task_timer;

	void ChangeTaskTarget(Character* performer, Vector2 target) {
		TaskForMove* currentTask = dynamic_cast<TaskForMove*>(performer->GetSchedule()->GetTask());
		if (currentTask == nullptr) return;
		currentTask->ChangeTarget(performer->GetPhysics().GetPosition(),target);
	}
	void ReserveWorldObject(WorldObject target, TaskReserveInfo task_reserve_info);
	void AddLeaveVillageTask(Character* character) {
		Vector2 leave_point = CoordinatesToCenterVector(character->GetSchedule()->GetVillageDeparturePoint());
		Task* new_task = new TaskForMove(now_tile_repo);
		ChangeTaskTarget(character, leave_point);
		character->GetSchedule()->SetTask(new_task);
	}
	void AddIdleTask(Character* performer) {
		Task* new_task = new TaskForIdleMove(now_tile_repo, performer);
		performer->GetSchedule()->SetTask(new_task);
	}
	void FindNewTaskToResident(Character* resident) {
		AddIdleTask(resident);
	}
	// To-do: hard coding -> algorithm which use DB
	void FindNewTaskToGuest(Character* guest) {
		vector<PurposeOfVisit*> purposes = ((GuestSchedule*)(guest->GetSchedule()))->GetPurposOfVisit();
		for (PurposeOfVisit* p : purposes) {
			if (p->CanExecute()) {
				// To-do: ������ �´� Ȱ�� �߰�
				AddIdleTask(guest);
				return;
			}
		}
		AddLeaveVillageTask(guest);
	}
	void AssignTaskToResidents() {
		for (Character* c : *residents) {
			if (!c->GetSchedule()->HasTask())
				FindNewTaskToResident(c);
		}
	}
	void AssignTaskToGuests() {
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
	AIManager() : assign_task_timer(Timer(ASSIGN_TASK_INTERVAL_TIME)) {}
	void SetGameWorld(GameWorldForAI* world) {
		game_world = world;
		characters = world->GetObjectRepository()->GetCharacters();
		guests = world->GetObjectRepository()->GetCharacters();
		residents = world->GetObjectRepository()->GetCharacters();
		
		now_tile_repo = world->GetTileMap();
	}
	void Update(float delta) {
		assign_task_timer.timeGo(delta);
		if (assign_task_timer.isTimeEnd()) {
			AssignTaskToWholeCharacter();
			assign_task_timer.reset();
		}

		ExecuteCharactersTask();
	}

	void ChangeTaskTargetWholeCharacter(Vector2 target) {
		for (Character* c : *characters) {
			if (c->GetSchedule()->HasTask() && c->GetSchedule()->GetTask()->GetTaskType() == eTaskType::TASK_MOVE)
				ChangeTaskTarget(c, target);
		}
	}
};