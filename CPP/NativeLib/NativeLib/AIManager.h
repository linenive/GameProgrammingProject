#pragma once
#include "Character.h"
#include "TaskReserveInfo.h"
#include "GameWorldForAI.h"
#include "AIExecuter.h"
#include "PathFinder.h"
#include "Task.h"

class AIManager {

private:
	GameWorldForAI* game_world;
	vector<Character*>* characters;
	AIExecuter* ai_executer;
	TileRepository* now_tile_repo;
	PathFinder path_finder = PathFinder();

	void FindNewTask(Character* performer) {
		// 임시로 600, 300 까지 이동하는 task 넣음
		Task* new_task = new Task(Vector2(600.0, 600.0));
		performer->GetSchedule()->SetTask(new_task);
	};
	void ChangeTaskTarget(Character* performer, Vector2 target) {
		Task* currentTask = performer->GetSchedule()->GetTask();
		currentTask->ChangeTarget(path_finder.PathFinding(performer->GetPhysics().GetPosition(), target), target);
	}
	void ReserveWorldObject(WorldObject target, TaskReserveInfo task_reserve_info);
	void AssignTaskToWholeCharacter() {
		for (Character* c : *characters) {
			if (!c->GetSchedule()->HasTask())
				FindNewTask(c);
		}
	};
	void ExecuteCharactersTask() {
		for (Character* c : *characters) {
			ai_executer->ExecuteCharacterTask(c);
		}
	}

public:
	void SetGameWorld(GameWorldForAI* world) {
		game_world = world;
		characters = world->GetObjectRepository()->GetCharacters();
		
		now_tile_repo = world->GetTileMap();
		path_finder.SetTileRepository(now_tile_repo);
	}
	void Update(float delta) {
		// To-do: 아래는 가끔씩만 업데이트해 주어도 괜찮음
		AssignTaskToWholeCharacter();
		ExecuteCharactersTask();
	};

	void ChangeTaskTargetWholeCharacter(Vector2 target) {
		for (Character* c : *characters) {
			if (c->GetSchedule()->HasTask())
				ChangeTaskTarget(c, target);
		}
	}
};