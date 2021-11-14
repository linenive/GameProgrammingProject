#pragma once
#include <vector>
#include "Common.h"
#include "Block.h"

using namespace std;

class StaticObject
{
public:
	string name;
	Rect2 ocupation_area;
	vector<Block*> blocks;

	StaticObject(string _name, Rect2 _ocupation_area) : name(_name), ocupation_area(_ocupation_area) {}

	void AddBlock(string _name, Transform2D _transform, Vector2 _scale)
	{
		blocks.push_back(new Block(_name, _transform, _scale, this));
	}

	void DeleteAllBlocks()
	{
		for (auto block : blocks)
			delete(block);
	}

	~StaticObject()
	{
		DeleteAllBlocks();
	}
};