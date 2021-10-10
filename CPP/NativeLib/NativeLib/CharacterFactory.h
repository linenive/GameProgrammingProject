#pragma once
#include "WorldObjectFactory.h"
#include "Character.h"

class CharacterFactory : public WorldObjectFactory {

protected:

public:
	WorldObject createObject() {
		Character new_character = Character();

		return new_character;
	}
};