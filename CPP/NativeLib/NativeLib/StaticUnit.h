#pragma once

#include <vector>
#include "Common.h"

class BlockInfo {
public:
	int x;
	int y;
	int layer_level;

	BlockInfo(int x, int y, int layer_level) : x(x), y(y), layer_level(layer_level) {};
};

class StaticUnit {
public:
	int id;
	string name;
	Rect2 ocupation_area;
	vector<BlockInfo> blocks;

	StaticUnit(int id, string _name, Rect2 _ocupation_area) : name(_name), ocupation_area(_ocupation_area) {}

	void RegisterBlockInfo(int x, int y, int layer_level)
	{
		blocks.push_back(BlockInfo(x, y, layer_level));
	}
};
