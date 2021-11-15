#pragma once
#include "Task.h"

class Schedule {
protected:
	Task* currentTask;

public:
	~Schedule() {
		if(currentTask != nullptr)
			delete currentTask;
	}
	Schedule():currentTask(nullptr){}
	Task* GetTask() { return currentTask; }
	void SetTask(Task* new_task) { currentTask = new_task; }
	bool HasTask() { return currentTask != nullptr; }
};
class GuestSchedule : public Schedule{
private:


};