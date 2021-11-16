#pragma once
#include "Tile.h"
#include "CoordinatesSystem.h"
#include "GameRule.h"
#include "CoordinatesSystem.h"

class TileRepository {
private:
	int tile_size_x;
	int tile_size_y;
	Tile* tile_map[MAX_TILE_NUMBER_Y][MAX_TILE_NUMBER_X];

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

	pair<int, int> TileIdToXy(int tile_id) {
		return { tile_id / DEFAULT_TILE_NUMBER_X, tile_id % DEFAULT_TILE_NUMBER_X };
	}

public:
	TileRepository() :tile_size_x(DEFAULT_TILE_NUMBER_X), tile_size_y(DEFAULT_TILE_NUMBER_Y) {
		CreateTileMapTemp();
	}

	int GetTileSize() { return tile_size_x * tile_size_y; }
	int GetTileSizeX() { return tile_size_x; }
	int GetTileSizeY() { return tile_size_y; }
	Tile* GetTile(int x, int y) { return tile_map[y][x]; }
	Surface* GetSurface(int tile_id) {
		pair<int, int> xy = TileIdToXy(tile_id);
		return GetSurface(xy.first, xy.second);
	}
	Surface* GetSurface(int x, int y) { return tile_map[y][x]->GetSurface(); }

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
	void SetBlockOnTile(int x, int y, int layer_index, string _name, StaticUnit* _owner)
	{
		tile_map[y][x]->SetBlock(layer_index, _name, _owner);
	}

	bool IsEmptySpace(int x, int y, int layer_index)
	{
		if (x >= MAX_TILE_NUMBER_X || x < 0 || y >= MAX_TILE_NUMBER_Y || y < 0)
			return false;
		return tile_map[x][y]->IsEmptyLayer(layer_index);
	}
};

