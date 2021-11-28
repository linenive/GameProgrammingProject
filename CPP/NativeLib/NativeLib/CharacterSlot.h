#pragma once

#include "Character.h"

class CharacterSlot {
private:
	Character* character;

public:
	CharacterSlot(Character* _character) {
		character = _character;
	}

	int GetCharacterId() {
		return character->GetId();
	}
};