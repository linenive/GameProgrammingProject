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

	// 블루프린트에서 사용하기 위해 추가함. 2차발표후 보이는대로 알맞게 처리하기.
	void SetBluePrintPosition(Vector2 position) {
		ocupation_area.set_position(position);
	}
};