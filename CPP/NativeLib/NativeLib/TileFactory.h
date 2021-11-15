#pragma once
#include "WorldObjectFactory.h"
#include "Tile.h"

class CharacterFactory : public WorldObjectFactory {

protected:


public:
	WorldObject CreateObject(Transform2D transform, Vector2 scale) {
		Tile new_tile = Tile(TILE_NONE, transform, scale);

		return new_tile;
	}
};