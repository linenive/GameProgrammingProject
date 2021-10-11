#pragma once
#include "WorldObject.h"
#include "Task.h"

class Character : public WorldObject {

private:
	Task* currentTask;

public:
	Character(Transform2D transform) : WorldObject("Noname", transform), currentTask(NULL){}
};