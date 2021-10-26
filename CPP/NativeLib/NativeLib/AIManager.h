#pragma once
#include "Character.h"
#include "TaskReserveInfo.h"
#include "GameWorldForUI.h"

class AIManager {

private:
	GameWorldForUI* game_world;

	void FindNewTask(Character performer);
	void AssignTaskToWholeCharacter();
	void ReserveWorldObject(WorldObject target, TaskReserveInfo task_reserve_info);

public:
	void SetGameWorld(GameWorldForUI* world) { game_world = world; }
};