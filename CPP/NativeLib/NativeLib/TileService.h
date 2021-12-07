#pragma once

#include "TileRepository.h"

class TileService {
private:
	TileRepository* tile_repo;

public:
	TileService(TileRepository* _tile_repo) : tile_repo(_tile_repo) {};

	Coordinates GetTileCoordinate(Vector2 position) {
		if (tile_repo->IsInvalidCoordinate(position))
			// To-do: enum Error msg. ex) InvalidPositionError
			return Coordinates(-1, -1);

		return AbsolutePositionToCoordinates(position);
	}

	float GetTilePassSpeed(Coordinates coord) {
		Tile* tile = tile_repo->GetTile(coord);
		if (tile == nullptr) return .0f;
		return tile->GetPassSpeed();
	}

	bool IsPassableTile(Coordinates coord) {
		Tile* tile = tile_repo->GetTile(coord);
		if (tile == nullptr) return false;
		return tile->GetPassSpeed() > 0.0;
	}

	bool IsEmptySpace(Coordinates coord, int layer_index) {
		Tile* tile = tile_repo->GetTile(coord);
		if (tile == nullptr) return false;
		return tile->IsEmptyLayer(layer_index);
	}

	Tile* GetTile(int x, int y) {
		return tile_repo->GetTile(x, y);
	}

	int GetTileSizeX() { return tile_repo->GetTileSizeX(); }
	int GetTileSizeY() { return tile_repo->GetTileSizeY(); }

	Surface* GetSurface(int x, int y) {
		return tile_repo->GetTile(x, y)->GetSurface();
	}

	Surface* GetSurface(Coordinates coord) {
		return tile_repo->GetTile(coord.x, coord.y)->GetSurface();
	}
};
