#pragma once
#include "WorldObject.h"
#include "Task.h"

class Character : public WorldObject {

private:
	Task* currentTask;

public:
	Character():currentTask(NULL){}
};