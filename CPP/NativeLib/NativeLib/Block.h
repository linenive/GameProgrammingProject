#pragma once

#include "GameRule.h"
#include "WorldObject.h"
#include "BlockTypeProperty.h"

class Block : public WorldObject {
private:

public:
	int owner_id;
	bool is_exist;
	eBlockType block_type;
	Block(string _name, Transform2D _new_transform, Vector2 _new_scale, int _owner_id)
		: WorldObject(_name, _new_transform, _new_scale), owner_id(_owner_id), is_exist(false), block_type(eBlockType::NONE) {
	}

	Block(string _name, Transform2D _new_transform, Vector2 _new_scale)
		: WorldObject(_name, _new_transform, _new_scale), is_exist(false), block_type(eBlockType::NONE) {
	}

	void Disappear() {
		is_exist = false;
	}

	float GetPassSpeed() {
		if (is_exist == false)
			return 1.0;
		return pass_speed;
	}

	void SetPassSpeed(float _pass_speed) {
		pass_speed = _pass_speed;
	}
};