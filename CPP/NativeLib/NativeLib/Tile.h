#pragma once
#include "WorldObject.h"

enum class eTileType {
	TILE_NONE, TILE_EARTH, TILE_ROCK, TILE_RIVER, TILE_OCEAN
};

class TileType {
private:
	string name;
public:
	TileType(eTileType tile_type) {
		type = tile_type;
		// To-do: 엑셀 문서를 읽는것으로 바꾸기
		if (type == eTileType::TILE_NONE)
			name = "empty";
		else if (type == eTileType::TILE_EARTH)
			name = "earth";
		else if (type == eTileType::TILE_ROCK)
			name = "rock";
		else if (type == eTileType::TILE_RIVER)
			name = "river";
		else if (type == eTileType::TILE_OCEAN)
			name = "ocean";
	}
	eTileType type;
	string GetName() { return name; }
};

class Tile : public WorldObject {

private:
	TileType tile_type;
public:
	Tile(TileType tile_type, Transform2D transform, Vector2 new_scale) : WorldObject(tile_type.GetName(),
		transform, new_scale), tile_type(tile_type) {}

	void SetTileType(TileType type) {
		tile_type = type;
		name = type.GetName();
	}

	TileType GetTileType() { return tile_type; }
};
