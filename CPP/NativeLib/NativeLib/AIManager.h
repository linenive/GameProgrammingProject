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
		Task* new_task = new Task(Vector2(600.0, 300.0));
		performer->SetTask(new_task);
	};
	void ChangeTaskTarget(Character* performer, Vector2 target) {

		Task* currentTask = performer->GetTask();
		currentTask->ChangeTarget(path_finder.PathFinding(performer->GetPhysics().getPosition(), target), target);

		//Godot::print("[AIManager] >>>> change target : " + performer->GetPhysics().getPosition());
		//path_finder.PathFinding(performer->GetPhysics().getPosition(), target);
	}
	void ReserveWorldObject(WorldObject target, TaskReserveInfo task_reserve_info);
	void AssignTaskToWholeCharacter() {
		for (Character* c : *characters) {
			if (!c->HasTask())
				FindNewTask(c);
		}
	};
	void ExecuteCharactersTask() {
		for (Character* c : *characters) {
			ai_executer->ExecuteCharacterTask(c);
		}
	}

public:
	void SetGameWorld(GameWorldForAI* world, TileRepository* tile) {
		game_world = world;
		characters = world->GetObjectRepository()->GetCharacters();
		
		now_tile_repo = tile;
		path_finder.SetTileRepository(tile);
	}
	void Update(float delta) {
		// To-do: �Ʒ��� �������� ������Ʈ�� �־ ������
		AssignTaskToWholeCharacter();
		ExecuteCharactersTask();
	};

	void ChangeTaskTargetWholeCharacter(Vector2 target) {
		for (Character* c : *characters) {
			if (c->HasTask())
				ChangeTaskTarget(c, target);
		}
	}
};