#pragma once
#include "Common.h"
#include "GameRule.h"

class IDRepository {
private:
	int type_id;
	int current_count;
public:
	IDRepository(int _type_id) :type_id(_type_id) {
		current_count = 0;
	}
	int GetNewID() {
		return type_id * ID_CODE_DIGIT + (current_count++);
	}
};