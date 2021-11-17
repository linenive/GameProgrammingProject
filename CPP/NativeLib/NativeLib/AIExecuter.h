#pragma once

class AIExecuter {

public:
	void ExecuteCharacterTask(Character* c) {
		Schedule* s = c->GetSchedule();
		if (s->HasTask()) {
			s->GetTask()->ExecuteTask(c);
		}
	}
};