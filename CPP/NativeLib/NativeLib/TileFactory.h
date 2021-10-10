#pragma once
#include "WorldObjectFactory.h"
#include "Tile.h"

class CharacterFactory :WorldObjectFactory {

protected:


public:
	WorldObject createObject() {
		Tile new_tile = Tile();

		return new_tile;
	}
};