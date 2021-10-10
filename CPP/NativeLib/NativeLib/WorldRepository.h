#pragma once
#include "TileMap.h"

// world object�� list�� �����Ͽ����� ���� quad-tree �ڷᱸ���� ����غ���.
class WorldRepository
{
private:
	TileMap tile_map;
	WorldObject** whole_objects;
	WorldObject** characters;

public:
	TileMap GetTileMap() { return tile_map; }
};

