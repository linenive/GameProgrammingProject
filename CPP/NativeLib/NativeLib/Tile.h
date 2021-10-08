#pragma once
#include "WorldObject.h"

enum eTileType {
	TILE_NONE, TILE_EARTH, TILE_ROCK, TILE_WATER
};

class Tile : public WorldObject{

private:
	eTileType tileType;
public:
	Tile() : tileType(TILE_NONE){}
	eTileType GetTileType() { return tileType; }
};

