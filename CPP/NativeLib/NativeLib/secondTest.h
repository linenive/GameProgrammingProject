#pragma once
#include "Common.h"
#include <Sprite.hpp>

class secondTest : public Sprite{
	GODOT_CLASS(secondTest, Sprite);
private:
	int speed;
	float time_passed;
public:
	static void _register_methods();

	void _process(float delta);
};

