#pragma once
#include "Tile.h"
#include "GameRule.h"

class TileMap {
private:
	int tile_size_x;
	int tile_size_y;
	Tile tile_map[MAX_TILE_NUMBER_Y*MAX_TILE_NUMBER_X];

	void CreateTileMapTemp();

public:
	TileMap() :tile_size_x(DEFAULT_TILE_NUMBER_X), tile_size_y(DEFAULT_TILE_NUMBER_Y) {
		CreateTileMapTemp();
	}

	int GetTileSize() { return tile_size_x * tile_size_y; }
	Tile GetTile(int tile_num) { return tile_map[tile_num]; }
};