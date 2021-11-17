#pragma once
#include "WorldObjectFactory.h"
#include "Character.h"

class CharacterFactory : public WorldObjectFactory {

protected:

public:
	WorldObject* createObject(Transform2D transform, Vector2 scale) {
		Character* new_character = new Character(transform, scale);

		return new_character;
	}
};