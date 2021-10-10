#pragma once
#include "WorldObject.h"

class WorldObjectFactory {

protected:
public:
	WorldObject createObject() {
		WorldObject new_world_object;

		return new_world_object;
 }
};