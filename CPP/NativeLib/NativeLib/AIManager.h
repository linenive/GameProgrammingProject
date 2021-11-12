#pragma once
#include "Character.h"
#include "TaskReserveInfo.h"
#include "GameWorldForAI.h"
#include "AIExecuter.h"
#include "Task.h"

class AIManager {

private:
	GameWorldForAI* game_world;
	vector<Character*>* characters;
	AIExecuter* ai_executer;

	void FindNewTask(Character* performer) {
		Task* new_task = new Task(Vector2(600.0, 300.0));
		performer->SetTask(new_task);
	};
	void ChangeTaskTarget(Character* performer, Vector2 target) {
		performer->GetTask()->SetTarget(target);
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