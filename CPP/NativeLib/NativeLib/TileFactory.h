#pragma once
#include "WorldObjectFactory.h"
#include "Tile.h"

class CharacterFactory : public WorldObjectFactory {

protected:


public:
	WorldObject createObject(Transform2D transform) {
		Tile new_tile = Tile(TILE_NONE, transform);

		return new_tile;
	}
};