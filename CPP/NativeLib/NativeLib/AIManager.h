#pragma once
#include "Character.h"
#include "TaskReserveInfo.h"
#include "GameWorldForAI.h"

class AIManager {

private:
	GameWorldForAI* game_world;
	vector<Character*>* characters;

	void FindNewTask(Character performer);
	void AssignTaskToWholeCharacter();
	void ReserveWorldObject(WorldObject target, TaskReserveInfo task_reserve_info);
	void ExecuteCharactersTask() {
		for (Character* c : *characters) {

		}
	}

public:
	void SetGameWorld(GameWorldForAI* world) {
		game_world = world;
		characters = world->GetObjectRepository()->GetCharacters();
	}
	void update(float delta) {
		// 리스트 잘 받아졌는지 테스트용
		if (characters->size() > 0) {
			Transform2D transform = (*characters)[0]->GetTransform();
			Vector2 vec = transform.get_origin();
			vec.x++;
			transform.set_origin(vec);
			(*characters)[0]->SetTransform(transform);
		}
		
	};
};