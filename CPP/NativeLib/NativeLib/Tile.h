#pragma once
#include "WorldObject.h"

enum eTileType {
	TILE_NONE, TILE_EARTH, TILE_ROCK, TILE_RIVER, TILE_OCEAN
};

class TileType {
private:
	string name;
public:
	TileType(eTileType tile_type) {
		type = tile_type;
		// To-do: 엑셀 문서를 읽는것으로 바꾸기
		if (type == TILE_NONE)
			name = "empty";
		else if (type == TILE_EARTH)
			name = "earth";
		else if (type == TILE_ROCK)
			name = "rock";
		else if (type == TILE_RIVER)
			name = "river";
		else if (type == TILE_OCEAN)
			name = "ocean";
	}
	eTileType type;
	string GetName() { return name; }
};

class Tile : public WorldObject {

private:
	TileType tile_type;
public:
	Tile(TileType tile_type, Transform2D transform) : WorldObject(tile_type.GetName(),
		transform), tile_type(tile_type) {}

	void SetTileType(TileType type) {
		tile_type = type;
		name = type.GetName();
	}

	TileType GetTileType() { return tile_type; }
};
