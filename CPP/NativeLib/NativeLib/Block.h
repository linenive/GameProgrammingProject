#pragma once

#include "GameRule.h"
#include "StaticUnit.h"
#include "WorldObject.h"

class Block : public WorldObject{
private:

public:
	StaticUnit* owner;
	bool is_exist;
	eBlockType block_type;
	Block(string _name, Transform2D _new_transform, Vector2 _new_scale, StaticUnit* _owner)
		: WorldObject(_name, _new_transform, _new_scale), owner(_owner), is_exist(false) {
		isPassThrough = false;
	}

	Block(string _name, Transform2D _new_transform, Vector2 _new_scale)
		: WorldObject(_name, _new_transform, _new_scale), is_exist(false) {
		isPassThrough = false;
	}

	void Disappear() {
		is_exist = false;
	}
};