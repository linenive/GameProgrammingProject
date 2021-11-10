#pragma once
#include "StaticObject.h"
#include "WorldObject.h"

class Block : public WorldObject
{
public:
	StaticObject* owner;
	Block(string _name, Transform2D _new_transform, Vector2 _new_scale, StaticObject* _owner)
		: WorldObject(_name, _new_transform, _new_scale), owner(_owner)
	{
		isPassThrough = false;
	}
};