#pragma once
#include <queue>

class AIExecuter {
private:
	void EndTask(Character* character) {
		Schedule* schedule = character->GetSchedule();
		if (schedule->GetTaskType()== eTaskType::LEAVE_VILLAGE) {
			schedule->PauseForDequeue();
			village_leavers.push(character->GetId());
			return;
		}
		character->GetSchedule()->DeleteTask();
	}

public:
	queue<int> village_leavers;

	void ExecuteCharacterTask(Character* character) {
		Schedule* schedule = character->GetSchedule();

		if (!schedule->HasTask()) { return; }

		if (schedule->IsPauseForDequeue()) {
			return;
		}
		else if (!schedule->IsTaskEnd()) {
			schedule->ExecuteTask(character->GetPhysics(), character->GetStatValue(eStatFieldType::BASE_MOVE_SPEED));
		}
		else {
			EndTask(character);
		}
	}

	

	
};