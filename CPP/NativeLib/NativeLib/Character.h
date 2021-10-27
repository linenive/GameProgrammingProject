#pragma once
#include "WorldObject.h"
#include "Task.h"

class Character : public WorldObject {

private:
	Task* currentTask;

public:
	Character(Transform2D transform, Vector2 scale) : WorldObject("Noname", transform, scale), currentTask(nullptr){}
	Task* GetTask() { return currentTask; }
	void SetTask(Task* new_task) { currentTask = new_task; }
	bool HasTask() { return currentTask != nullptr; }
};