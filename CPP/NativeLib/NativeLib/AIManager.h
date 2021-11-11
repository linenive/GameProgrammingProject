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
		// 임시로 600, 300 까지 이동하는 task 넣음
		Task* new_task = new Task(Vector2(600.0, 300.0));
		performer->SetTask(new_task);
	};
	void ChangeTaskTarget(Character* performer, Vector2 target) {
		// 이후 이동 task만 Get 하는것을 추가해야할듯
		performer->GetTask()->SetTarget(target);
<<<<<<< HEAD
		//path_finder->PathFinding(performer->GetPhysics().getPosition(), target);
=======
>>>>>>> parent of 808e53e (yojin-6/#7 Pathfinder �옉�꽦以� CoordinatesSystem�삤瑜� �솗�씤)
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
		// To-do: 아래는 가끔씩만 업데이트해 주어도 괜찮음
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