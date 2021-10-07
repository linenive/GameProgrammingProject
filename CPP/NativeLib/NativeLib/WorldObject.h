#pragma once
#include "Common.h"
#include "GameRule.h"

enum ObjectHeightLevel {

};

class WorldObject{

private:
	Transform transform;
	bool isPassThrough;
	char* name[MAX_GAMEOBJECT_NAME_SIZE];
	
};

