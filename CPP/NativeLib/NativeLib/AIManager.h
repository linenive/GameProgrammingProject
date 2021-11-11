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
		// ÀÓ½Ã·Î 600, 300 ±îÁö ÀÌµ¿ÇÏ´Â task ³ÖÀ½
		Task* new_task = new Task(Vector2(600.0, 300.0));
		performer->SetTask(new_task);
	};
	void ChangeTaskTarget(Character* performer, Vector2 target) {
		// ÀÌÈÄ ÀÌµ¿ task¸¸ Get ÇÏ´Â°ÍÀ» Ãß°¡ÇØ¾ßÇÒµí
		performer->GetTask()->SetTarget(target);
<<<<<<< HEAD
		//path_finder->PathFinding(performer->GetPhysics().getPosition(), target);
=======
>>>>>>> parent of 808e53e (yojin-6/#7 Pathfinder ìž‘ì„±ì¤‘ CoordinatesSystemì˜¤ë¥˜ í™•ì¸)
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
		// To-do: ¾Æ·¡´Â °¡²û¾¿¸¸ ¾÷µ¥ÀÌÆ®ÇØ ÁÖ¾îµµ ±¦ÂúÀ½
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