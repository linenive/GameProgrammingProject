#pragma once

#include <vector>
#include "Common.h"
#include "Block.h"

class StaticUnit {
public:
	int id;
	string name;
	Rect2 ocupation_area;
	vector<Block*> blocks;

	StaticUnit(int id, string _name, Rect2 _ocupation_area) : name(_name), ocupation_area(_ocupation_area) {}

	void RegisterBlock(Block* block)
	{
		blocks.push_back(block);
	}
};