#pragma once
#include <queue>

class AIExecuter {
private:
	void EndTask(Character* character, Task* task) {
		if (task->GetType()== eTaskType::LEAVE_VILLAGE) {
			village_leavers.push(character->GetId());
			return;
		}
		delete task;
		task = nullptr;
	}

public:
	queue<int> village_leavers;

	void ExecuteCharacterTask(Character* character, Task* task) {
		if (task==nullptr) { return; }
		else if (task->HasAction()) {
			task->Execute(character);
		}
		else {
			EndTask(character, task);
		}
	}

	

	
};