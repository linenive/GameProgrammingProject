#pragma once
#include "WorldObject.h"

class WorldObjectFactory {

protected:
public:
	WorldObject createObject(Transform2D transform) {
		WorldObject new_character = WorldObject("NoName", transform);

		return new_character;
	}
};