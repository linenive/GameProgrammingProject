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

public:
	TileRepository() :tile_size_x(DEFAULT_TILE_NUMBER_X), tile_size_y(DEFAULT_TILE_NUMBER_Y) {	}
	int GetTileSizeX() { return tile_size_x; }
	int GetTileSizeY() { return tile_size_y; }
	Tile* GetTile(int x, int y) { 
		if (IsInvalidCoordinate(Coordinates(x, y))) {
			printf("WARNING: [TileRepository]trying to get not exist tile! ");
			printf("input coordinate: (%d, %d)\n", x, y);
			return nullptr;
		}
		return tile_map[y][x];
	}
	Tile* GetTile(Coordinates coord) {
		if (IsInvalidCoordinate(coord)) {
			printf("WARNING: [TileRepository]trying to get not exist tile! ");
			printf("input coordinate: (%d, %d)\n", coord.x, coord.y);
			return nullptr;
		}
		return tile_map[coord.y][coord.x];
	}

	void InitTile(int x, int y, SurfaceType type, Vector2 position) {
		tile_map[y][x] = new Tile(type, position);
	}

	bool UpdateTileType(Coordinates coord, SurfaceType type) {
		Tile* tile = GetTile(coord);
		if (tile == nullptr) return false;
		tile->SetSurfaceType(type);
		return true;
	}

	bool IsInvalidCoordinate(Coordinates coord) {
		return coord.x >= tile_size_x || coord.x < 0 || coord.y >= tile_size_y || coord.y < 0;
	}

	bool IsInvalidCoordinate(Vector2 vector) {
		Coordinates coord = AbsolutePositionToCoordinates(vector);
		return IsInvalidCoordinate(coord);
	}
};