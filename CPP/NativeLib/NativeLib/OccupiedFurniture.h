#pragma once
#include "Furniture.h"
#include "Character.h"

class OccupiedFurnitureItem : public FurnitureItem {
private:
	Character* current_use_character = nullptr;

public:
	~OccupiedFurnitureItem() {
		delete current_use_character;
	}
	bool IsVacant() {
		return current_use_character == nullptr;
	}
	bool SetOccupiedCharacter(Character* new_character) {
		if (IsVacant()) {
			current_use_character = new_character;
			return true;
		}
		return false;
	}
	Character* LeaveOccupiedCharacter() {
		if (IsVacant()) return nullptr;

		Character* last_character = current_use_character;
		current_use_character = nullptr;

		return last_character;
	}
};