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

	// �������Ʈ���� ����ϱ� ���� �߰���. 2����ǥ�� ���̴´�� �˸°� ó���ϱ�.
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