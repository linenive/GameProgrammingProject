#pragma once
#include "WorldObjectFactory.h"
#include "Character.h"

class CharacterFactory : public WorldObjectFactory {

protected:

public:
	WorldObject* createObject(Transform2D transform) {
		Character* new_character = new Character(transform);

		return new_character;
	}
};