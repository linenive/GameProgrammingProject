#pragma once
#include "Tile.h"
#include "GameRule.h"
#include "CoordinatesSystem.h"

// world object�� vector�� �����Ͽ����� ���� quad-tree �ڷᱸ���� ����غ���.
class TileRepository{
private:
	int tile_size_x;
	int tile_size_y;
	Tile* tile_map[MAX_TILE_NUMBER_Y * MAX_TILE_NUMBER_X];

	void CreateTileMapTemp();

public:
	TileRepository() :tile_size_x(DEFAULT_TILE_NUMBER_X), tile_size_y(DEFAULT_TILE_NUMBER_Y) {

		CreateTileMapTemp();
	}

	int GetTileSize() { return tile_size_x * tile_size_y; }
	int GetTileSizeX() { return tile_size_x; }
	int GetTileSizeY() { return tile_size_y; }
	Tile GetTile(int tile_num) { return *tile_map[tile_num]; }
	int GetTileNumber(Coordinates coord);
};

