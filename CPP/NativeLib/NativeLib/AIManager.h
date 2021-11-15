#pragma once
#include "Character.h"
#include "TaskReserveInfo.h"
#include "GameWorldForAI.h"
#include "AIExecuter.h"
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
	PathFinder path_finder = PathFinder();

	Timer assign_task_timer;

	void ReserveWorldObject(WorldObject target, TaskReserveInfo task_reserve_info);
	void AddTempTask(Character* character) {
		// 임시로 600, 300 까지 이동하는 task 넣음
		Task* new_task = new Task(Vector2(600.0, 600.0));
		character->GetSchedule()->SetTask(new_task);
	}
	void ChangeTaskTarget(Character* performer, Vector2 target) {
		Task* currentTask = performer->GetSchedule()->GetTask();
		currentTask->ChangeTarget(path_finder.PathFinding(performer->GetPhysics().GetPosition(), target), target);
	}
	void ReserveWorldObject(WorldObject target, TaskReserveInfo task_reserve_info);
	void AddLeaveVillageTask(Character* character) {
		Task* new_task = new Task(CoordinatesToCenterVector(character->GetSchedule()->GetVillageDeparturePoint()));
		character->GetSchedule()->SetTask(new_task);
	}
	void FindNewTaskToResident(Character* resident) {
		AddTempTask(resident);
	}
	// To-do: hard coding -> algorithm which use DB
	void FindNewTaskToGuest(Character* guest) {
		vector<PurposeOfVisit*> purposes = ((GuestSchedule*)(guest->GetSchedule()))->GetPurposOfVisit();
		for (PurposeOfVisit* p : purposes) {
			if (p->CanExecute()) {
				// To-do: 목적에 맞는 활동 추가
				AddTempTask(guest);
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
		path_finder.SetTileRepository(now_tile_repo);
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
			if (c->GetSchedule()->HasTask())
				ChangeTaskTarget(c, target);
		}
	}
};