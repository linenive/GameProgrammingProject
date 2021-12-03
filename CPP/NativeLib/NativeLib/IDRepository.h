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
	bool operator==(const IDRepository& other) const {
		if (type_id == other.type_id) {
			return true;
		}
		else {
			return false;
		}
	}
	int GetNewID() {
		int new_id = type_id * ID_CODE_DIGIT + current_count;
		current_count++;
		return new_id;
	}
};