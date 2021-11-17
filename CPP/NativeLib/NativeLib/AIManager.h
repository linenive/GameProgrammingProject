#pragma once
#include "Character.h"
#include "TaskReserveInfo.h"
#include "GameWorldForAI.h"
#include "AIExecuter.h"
#include "TaskForIdleMove.h"

class AIManager {

private:
	GameWorldForAI* game_world;
	vector<Character*>* characters;
	AIExecuter* ai_executer;
	TileRepository* now_tile_repo;

	void FindNewTask(Character* performer) {
		//TaskForMove* new_task = new TaskForMove(now_tile_repo);
		TaskForIdleMove* new_task = new TaskForIdleMove(now_tile_repo, performer);
		performer->SetTask(new_task);
	};
	void ChangeTaskTarget(Character* performer, Vector2 target) {

		TaskForMove* currentTask = dynamic_cast<TaskForMove*>(performer->GetTask());
		currentTask->ChangeTarget(performer->GetPhysics().GetPosition(),target);
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
	void SetGameWorld(GameWorldForAI* world) {
		game_world = world;
		characters = world->GetObjectRepository()->GetCharacters();
		
		now_tile_repo = world->GetTileMap();
	}
	void Update(float delta) {
		// To-do: �Ʒ��� �������� ������Ʈ�� �־ ������
		AssignTaskToWholeCharacter();
		ExecuteCharactersTask();
	};

	void ChangeTaskTargetWholeCharacter(Vector2 target) {
		for (Character* c : *characters) {
			if (c->HasTask() && c->GetTask()->GetTaskType() == eTaskType::TASK_MOVE)
				ChangeTaskTarget(c, target);
		}
	}
};