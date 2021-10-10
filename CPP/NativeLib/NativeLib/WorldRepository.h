#pragma once
#include "TileMap.h"

class WorldRepository
{
private:
	TileMap tile_map;
public:
	TileMap GetTileMap() { return tile_map; }
};

