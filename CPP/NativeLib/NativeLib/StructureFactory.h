#pragma once
#include "WorldObjectFactory.h"
#include "Structure.h"

class StructureFactory : public WorldObjectFactory {

protected:


public:
	WorldObject createObject(Transform2D transform, Vector2 scale) {
		Structure new_tile = Structure("noname", transform, scale, A);

		return new_tile;
	}
};