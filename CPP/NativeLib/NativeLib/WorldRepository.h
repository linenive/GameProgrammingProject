#pragma once
#include "Tile.h"
#include "GameRule.h"

class WorldRepository
{
private:
	Tile tile_map[MAX_TILE_Y][MAX_TILE_X];
	int tile_size_x;
	int tile_size_y;

	void CreateTileMapTemp();

public:
	WorldRepository();
	
};

