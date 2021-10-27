#pragma once
#include <string>
#include "Common.h"
#include "GameRule.h"
#include "TaskReserveInfo.h"
#include "Physics.h"

class WorldObject {

protected:
	Physics physics;
	Vector2 scale;
	bool isPassThrough;
	string name;
	TaskReserveInfo reserveInfo;

public:
	string GetName() { return name; }
	void SetName(string name) { this->name = name; }
	Physics GetPhysics() { return physics; }
	void SetPhysics(Physics physics) { this->physics = physics; }
	Vector2 GetScale() { return scale; }

	WorldObject(string name, Transform2D new_transform, Vector2 new_scale) :
		name(name), physics(new_transform), scale(new_scale){}
};
