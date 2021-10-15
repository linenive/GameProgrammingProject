#pragma once
#include <string>
#include "Common.h"
#include "GameRule.h"
#include "TaskReserveInfo.h"

class WorldObject {

protected:
	Transform2D transform;
	Vector2 scale;
	bool isPassThrough;
	string name;
	TaskReserveInfo reserveInfo;

public:
	string GetName() { return name; }
	void SetName(string name) { this->name = name; }
	Transform2D GetTransform() { return transform; }
	Vector2 GetScale() { return scale; }
	void SetTransform(Transform2D new_transform) { transform = new_transform; }

	WorldObject(string name, Transform2D new_transform, Vector2 new_scale) :
		name(name), transform(new_transform), scale(new_scale){}
};
