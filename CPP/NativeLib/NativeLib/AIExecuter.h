#pragma once
#include <vector>

class AIExecuter {
private:

public:
	void ExecuteCharacterTask(Character* character) {
		Schedule* schedule = character->GetSchedule();
		if (schedule->HasTask()) {
			Task* task = schedule->GetTask();
			if (!task->IsEnd()) {
				task->Execute(character);
			} else {
				schedule->DeleteTask();
			}
		}
	}
};