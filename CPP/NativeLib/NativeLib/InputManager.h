#pragma once
#include "Common.h"
#include "GameManager.h"
#include "ControlState.h"
#include <Node.hpp>
#include <InputEventMouseButton.hpp>

class InputManager : public Node {
	GODOT_CLASS(InputManager, Node);

private:
	ControlContext control_context;
	GameWorldForInput* game_world;
	Vector2 now_mouse_point;

	void LoadGameWorld();

public:
	
	static void _register_methods();
	void _init();
	void _ready();

	void MouseClick(Vector2 position);
	void MouseRelease(Vector2 position);
	void MouseHover(Vector2 position);

	bool IsDragging();
	void TestStructureButton();
	Rect2 GetDragRect();

};