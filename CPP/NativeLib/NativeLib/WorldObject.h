#pragma once
#include <string>
#include "Common.h"
#include "GameRule.h"
#include "TaskReserveInfo.h"

class WorldObject {

protected:
	Transform2D transform;
	bool isPassThrough;
	string name;
	TaskReserveInfo reserveInfo;

public:
	string GetName() { return name; }
	void SetName(string name) { this->name = name; }
	Transform2D GetTransform() { return transform; }
	void SetTransform(Transform2D new_transform) { transform = new_transform; }

	WorldObject(string name, Transform2D new_transform) :
		name(name), transform(new_transform) {}
};
