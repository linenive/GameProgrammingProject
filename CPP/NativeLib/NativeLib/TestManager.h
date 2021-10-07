#pragma once
#include "testProperty.h"
#include <CanvasLayer.hpp>

class TestManager : public CanvasLayer
{
	GODOT_CLASS(TestManager, CanvasLayer);

private:
	Skill skill = Skill(0, "noname");
	int test_c;

public:
	static void _register_methods();

	void _init();
	void _ready();
	void _process(float delta);
	void _physics_process(float delta);

	void pull(Variant from, float magnitude);

	int getSkillLevel() { return skill.GetLevel(); }
	godot::String getSkillName() { return skill.GetName(); }
	int getTestDataA() { return skill.GetDataA(); }
	bool getTestDataB() { return skill.GetDataB(); }
};

