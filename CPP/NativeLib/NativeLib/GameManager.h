#pragma once
#include "Common.h"
#include "GameWorld.h"
#include <CanvasLayer.hpp>

class GameManager : public CanvasLayer{
	GODOT_CLASS(GameManager, CanvasLayer);

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
};