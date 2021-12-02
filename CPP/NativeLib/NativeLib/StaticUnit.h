#pragma once

#include <vector>
#include "Common.h"
#include "Block.h"
#include "SerializableClass.h"

class StaticUnit : SerializableClass {
public:
	int id;
	string name;
	Rect2 ocupation_area;
	vector<Block*> blocks;

	StaticUnit(int id, string _name, Rect2 _ocupation_area) : id(id), name(_name), ocupation_area(_ocupation_area) {}

	void RegisterBlock(Block* block)
	{
		blocks.push_back(block);
	}

	Vector2 GetCenterPosition() {
		Vector2 position = ocupation_area.get_position();
		Vector2 size = ocupation_area.get_size();
		return Vector2(position.x + size.x / 2, position.y + size.y / 2);
	}

	Vector2 GetTopLeftBlockPosition() {
		return blocks[0][0].GetPhysics()->GetPosition();
	}

	// 블루프린트에서 사용하기 위해 추가함. 2차발표후 보이는대로 알맞게 처리하기.
	void SetBluePrintPosition(Vector2 position) {
		ocupation_area.set_position(position);
	}

	virtual Array Serialize() {
		Array serialized_data = Array();
		serialized_data.append(id);
		serialized_data.append(String(name.c_str()));
		return serialized_data;
	}
};