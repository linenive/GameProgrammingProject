#pragma once
#include "Common.h"
#include "testProperty.h"
#include <Node.hpp>

class TestManager : public Node
{
	GODOT_CLASS(TestManager, Node);

private:
	Skill skill = Skill(0, "noname");
	int test_c;

	float screenBounds_left;
	float screenBounds_right;
	float screenBounds_up;
	float screenBounds_down;

	void DetectScreenBounds(Vector2 newScreenSize);

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
	
	void SetScreenSize(Vector2 nowScreenSize);
	void SetTarget(Vector2 pos);
	void ReleaseTarget(Vector2 pos);

};

