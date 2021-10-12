#pragma once
#include "WorldObject.h"

class WorldObjectFactory {

protected:
public:
	WorldObject createObject(Transform2D transform, Vector2 scale) {
		WorldObject new_character = WorldObject("NoName", transform, scale);

		return new_character;
	}
};