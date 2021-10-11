#pragma once
#pragma once
#include "Common.h"
#include "GameManager.h"
#include <Node.hpp>

class InputManager : public Node {
	GODOT_CLASS(InputManager, Node);

private:
	GameWorldForInput* game_world;
	void LoadGameWorld();

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _process(float delta);

};