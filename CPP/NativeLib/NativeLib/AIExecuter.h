#pragma once
#include "Character.h"
#include "Task.h"
#include <queue>

class AIExecuter {
private:
	void EndTask(Character* character, Task* task) {
		if (task->GetType()== eTaskType::LEAVE_VILLAGE) {
			village_leavers.push(character->GetId());
			return;
		}
	}

public:
	queue<int> village_leavers;

	void ExecuteCharacterTask(Character* character, Task* task) {
		

		if (task==nullptr) { return; }
		else if (!task->IsTaskDone() && task->HasAction()) {
			task->Execute(character);
		}
		else {			
			EndTask(character, task);
		}
	}
};