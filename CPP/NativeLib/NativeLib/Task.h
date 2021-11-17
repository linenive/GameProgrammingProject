#pragma once
#include "WorldObject.h"

enum class eTaskType {
	TASK_NONE, TASK_IDLE, TASK_MOVE
};

class Task{
protected:
	eTaskType type;
public:
	Task(){
		type = eTaskType::TASK_NONE;
	}
	~Task() {}
	virtual void ExecuteTask(WorldObject* performer);
	virtual void ClearTask();
	eTaskType GetTaskType(){ return type; }
};