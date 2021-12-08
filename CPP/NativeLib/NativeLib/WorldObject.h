#pragma once
#include <string>
#include "Common.h"
#include "GameRule.h"
#include "TaskReserveInfo.h"
#include "Physics.h"
#include "SerializableClass.h"

class WorldObject : SerializableClass {

protected:
	Physics* physics;
	float pass_speed;
	string name;
	TaskReserveInfo reserve_info;

public:
	~WorldObject() {
		delete physics;
	}
	string GetName() { return name; }
	void SetName(string name) { this->name = name; }
	Physics* GetPhysics() { return physics; }

	WorldObject(string name, Transform2D new_transform, Vector2 new_scale) :
		name(name), physics(new Physics(new_transform, new_scale)){}

	virtual Array Serialize() {
		Array serialized_data = Array();
		serialized_data.append(String(name.c_str()));
		return serialized_data;
	}
};
