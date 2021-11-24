#pragma once

#include "TileRepository.h"

class TileService {
private:
	TileRepository* tile_repo;

public:
	TileService(TileRepository* _tile_repo) : tile_repo(_tile_repo) {};

	Vector2 GetTileCoordinate(Vector2 position) {
		Coordinates coord = tile_repo->GetTileCoordinate(position);
		return Vector2(coord.x, coord.y);
	}

	float GetTilePassSpeed(int x, int y) {
		return tile_repo->GetTilePassSpeed(x, y);
	}

	int GetTileSizeX() { return tile_repo->GetTileSizeX(); }
	int GetTileSizeY() { return tile_repo->GetTileSizeY(); }

	Surface* GetSurface(int x, int y) {
		return tile_repo->GetSurface(x, y);
	}
};
