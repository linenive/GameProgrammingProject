#pragma once
#include "WorldObject.h"

enum eTileType {
	TILE_NONE, TILE_EARTH, TILE_ROCK, TILE_WATER
};

class Tile : public WorldObject{

private:
	eTileType tile_type;
public:
	Tile() : tile_type(TILE_NONE){}
	eTileType GetTileType() { return tile_type; }
};
