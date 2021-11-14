#pragma once
#include "Tile.h"
#include "CoordinatesSystem.h"
#include "GameRule.h"
#include "CoordinatesSystem.h"

class TileRepository {
private:
	int tile_size_x;
	int tile_size_y;
	Tile* tile_map[MAX_TILE_NUMBER_Y * MAX_TILE_NUMBER_X];

	void CreateTileMapTemp();

	int CalculateTileNumberByCoordinates(Coordinates coord) {
		return coord.x + tile_size_x * coord.y;
	}

	bool IsInWorld(Coordinates coord) {
		return (
			coord.x > -1 && coord.x < tile_size_x&&
			coord.y > -1 && coord.y < tile_size_y
			);
	}

	bool IsInWorld(Vector2 vector) {
		Coordinates hovered_tile = AbsolutePositionToCoordinates(vector);
		return IsInWorld(hovered_tile);
	}

public:
	TileRepository() :tile_size_x(DEFAULT_TILE_NUMBER_X), tile_size_y(DEFAULT_TILE_NUMBER_Y) {

		CreateTileMapTemp();
	}

	int GetTileSize() { return tile_size_x * tile_size_y; }
	int GetTileSizeX() { return tile_size_x; }
	int GetTileSizeY() { return tile_size_y; }
	Tile GetTile(int tile_num) { return *tile_map[tile_num]; }
	Surface GetSurface(int tile_num) { return (*tile_map[tile_num]).GetSurface(); }

	int GetTileId(Vector2 vector) {
		if (IsInWorld(vector)) {
			Coordinates hovered_tile = AbsolutePositionToCoordinates(vector);
			return CalculateTileNumberByCoordinates(hovered_tile);
		}
		else {
			// To-do: enumï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Úµï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ï±ï¿½: InvalidPositionError
			return -1;
		}
	}

	// StaticObject °ü·Ã
	void AddBlockOnTile(Block* block, int tile_num, int layer_num)
	{
		tile_map[tile_num]->SetBlock(block, layer_num);
	}

	bool IsEmptySpace(int tile_num, int layer_num)
	{
		if (tile_num >= MAX_TILE_NUMBER_Y * MAX_TILE_NUMBER_X)
			return false;
		return tile_map[tile_num]->IsEmptyLayer(layer_num);
	}
};
