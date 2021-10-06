#pragma once
#include "Common.h"
#include <CanvasLayer.hpp>

class UIManager : public CanvasLayer {
	GODOT_CLASS(UIManager, CanvasLayer);

public:
	static void _register_methods();
	void get_time();
	void _init();
	void _ready();
	void _process(float delta);
	void _physics_process(float delta);
};