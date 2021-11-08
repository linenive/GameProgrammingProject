#pragma once
#include "Tile.h"
#include "CoordinatesSystem.h"
#include "GameRule.h"

// world object를 vector로 구현하였으나 이후 quad-tree 자료구조를 고려해본다.
class TileRepository{
private:
	int tile_size_x;
	int tile_size_y;
	Tile* tile_map[MAX_TILE_NUMBER_Y * MAX_TILE_NUMBER_X];

	void CreateTileMapTemp();

	bool CheckCoordinatesInTileMap(Coordinates coord){
		return (
			coord.x > -1 && coord.x < tile_size_x &&
			coord.y > -1 && coord.y < tile_size_y
			);
	}

	int CalculateTileNumberByCoordinates(Coordinates coord){
		return coord.x + tile_size_x * coord.y;
	}

	bool IsInWorld(Vector2 vector) {
		Coordinates hovered_tile = AbsolutePositionToCoordinates(vector);
		return CheckCoordinatesInTileMap(hovered_tile);
	}

public:
	TileRepository() :tile_size_x(DEFAULT_TILE_NUMBER_X), tile_size_y(DEFAULT_TILE_NUMBER_Y) {

		CreateTileMapTemp();
	}

	int GetTileSize() { return tile_size_x * tile_size_y; }
	int GetTileSizeX() { return tile_size_x; }
	int GetTileSizeY() { return tile_size_y; }
	Tile GetTile(int tile_num) { return *tile_map[tile_num]; }

	int GetTileId(Vector2 vector) {
		if (IsInWorld(vector)) {
			Coordinates hovered_tile = AbsolutePositionToCoordinates(vector);
			return CalculateTileNumberByCoordinates(hovered_tile);
		}
		else {
			// To-do: enum으로 에러 코드 관리하기: InvalidPositionError
			return -1;
		}
	}
};

