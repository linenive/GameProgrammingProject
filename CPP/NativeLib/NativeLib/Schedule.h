#pragma once
#include "Task.h"

class Schedule {
protected:
	Task* currentTask;

public:
	Task* GetTask() { return currentTask; }
	void SetTask(Task* new_task) { currentTask = new_task; }
	bool HasTask() { return currentTask != nullptr; }
};
class GuestSchedule : public Schedule{
private:


};