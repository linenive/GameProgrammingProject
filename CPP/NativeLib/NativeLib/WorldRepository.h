#pragma once
#include "TileMap.h"

// world object를 list로 구현하였으나 이후 quad-tree 자료구조를 고려해본다.
class WorldRepository
{
private:
	TileMap tile_map;
	WorldObject** whole_objects;
	WorldObject** characters;

public:
	TileMap GetTileMap() { return tile_map; }
};

