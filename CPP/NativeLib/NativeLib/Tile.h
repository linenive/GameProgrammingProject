#pragma once
#include "WorldObject.h"

enum eTileType {
	TILE_NONE, TILE_EARTH, TILE_ROCK, TILE_WATER
};

class Tile : public WorldObject {

private:
	eTileType tile_type;
	string TileNameFromType(eTileType tile_type) {
		return "NoNameTile";
	}
public:
	Tile(eTileType tile_type, Transform2D transform) : WorldObject(TileNameFromType(tile_type),
		transform), tile_type(tile_type) {}

	eTileType GetTileType() { return tile_type; }
};
