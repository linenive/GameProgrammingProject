#pragma once
#include "Tile.h"
#include "CoordinatesSystem.h"
#include "GameRule.h"
#include "CoordinatesSystem.h"

class TileRepository {
private:
	int tile_size_x;
	int tile_size_y;
	Tile* tile_map[DEFAULT_TILE_NUMBER_Y][DEFAULT_TILE_NUMBER_X];

	void CreateTileMapTemp();

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
	TileRepository() :tile_size_x(DEFAULT_TILE_NUMBER_X), tile_size_y(DEFAULT_TILE_NUMBER_Y) {	}
	int GetTileSizeX() { return tile_size_x; }
	int GetTileSizeY() { return tile_size_y; }
	Tile* GetTile(int x, int y) { 
		if (!IsInWorld(Coordinates(x, y))) {
			printf("WARNING: [TileRepository]trying to get not exist tile! ");
			printf("input coordinate: (%d, %d)\n", x, y);
			return nullptr;
		}
		return tile_map[y][x];
	}
	void InitTile(int x, int y, SurfaceType type, Vector2 position) {
		tile_map[y][x] = new Tile(type, position);
	}
	void UpdateTileType(int x, int y, SurfaceType type) {
		tile_map[y][x]->SetSurfaceType(type);
	}
	Surface* GetSurface(int x, int y) { return tile_map[y][x]->GetSurface(); }
	Surface* GetSurface(Coordinates coord) { return tile_map[coord.y][coord.x]->GetSurface();}

	Coordinates GetTileCoordinate(Vector2 vector) {
		if (IsInWorld(vector)) {
			Coordinates hovered_tile = AbsolutePositionToCoordinates(vector);
			return hovered_tile;
		}
		else {
			// To-do: enum���� ���� �ڵ� �����ϱ�: InvalidPositionError
			return Coordinates(-1, -1);
		}
	}

	bool IsEmptySpace(int x, int y, int layer_index) {
		if (x >= DEFAULT_TILE_NUMBER_X || x < 0 || y >= DEFAULT_TILE_NUMBER_Y || y < 0)
			return false;
		return tile_map[y][x]->IsEmptyLayer(layer_index);
	}

	bool IsPassableTile(int x, int y) {
		if (x >= DEFAULT_TILE_NUMBER_X || x < 0 || y >= DEFAULT_TILE_NUMBER_Y || y < 0)
			return false;
		return tile_map[y][x]->GetPassSpeed() > 0.0;
	}

	float GetTilePassSpeed(int x, int y) {
		if (x >= DEFAULT_TILE_NUMBER_X || x < 0 || y >= DEFAULT_TILE_NUMBER_Y || y < 0)
			return false;
		return tile_map[y][x]->GetPassSpeed();
	}
};