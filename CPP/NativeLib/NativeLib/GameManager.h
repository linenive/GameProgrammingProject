#pragma once
#include "Common.h"
#include "GameWorld.h"
#include <Node.hpp>

class GameManager : public Node {
	GODOT_CLASS(GameManager, Node);

private:
	GameWorld game_world;

	void NewGame();
	void LoadGame();

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _process(float delta);
	void _physics_process(float delta);

	GameWorld* GetGameWorld() { return &game_world; }
};