#pragma once
#include "Common.h"
#include "GameManager.h"
#include <Node.hpp>

class UIManager : public Node {
	GODOT_CLASS(UIManager, Node);

private:
	GameWorldForUI* game_world;
	void GetGameWorld();

public:
	static void _register_methods();
	void _init() { GetGameWorld(); };
	void _process(float delta) {};

	int GetYear();
	int GetMonth();
	int GetDay();
	int GetHour();
	int GetMinute();
};