#pragma once
#include "WorldObject.h"
#include "Task.h"

class Character : public WorldObject {

private:
	Task* currentTask;

public:
	Character(Transform2D transform, Vector2 scale) : WorldObject("Noname", transform, scale), currentTask(NULL){}
};