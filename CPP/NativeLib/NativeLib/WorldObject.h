#pragma once
#include <string>
#include "Common.h"
#include "GameRule.h"
#include "TaskReserveInfo.h"

class WorldObject{

private:
	Transform2D transform;
	bool isPassThrough;
	char name[MAX_GAMEOBJECT_NAME_SIZE];
	TaskReserveInfo reserveInfo;

public:
	char* GetName() { return name; }
	void SetName(char name[]) { strcpy(this->name, name); }
	Transform2D GetTransform() { return transform; }
	void SetTransform(Transform2D new_transform) { transform = new_transform; }
};
