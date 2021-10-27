#pragma once

class AIExecuter {

public:
	void ExecuteCharacterTask(Character* c) {
		c->GetTask()->ExecuteTask(c);
	}
};