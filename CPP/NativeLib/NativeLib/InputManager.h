#pragma once
#include "Common.h"
#include "GameManager.h"
#include "ControlState.h"
#include "StaticUnitService.h"
#include <Node.hpp>
#include <InputEventMouseButton.hpp>

class InputManager : public Node {
	GODOT_CLASS(InputManager, Node);

private:
	ControlContext* control_context;
	StaticUnitService* static_unit_service;
	GameWorldForInput* game_world;
	Vector2 now_mouse_point;
	Vector2 now_mouse_right_click_point;

	void LoadGameWorld();

public:
	~InputManager() {
		delete control_context;
		delete static_unit_service;
	}
	
	static void _register_methods();
	void _init();
	void _ready();

	void MouseClick(Vector2 position);
	void MouseRightClick(Vector2 position);
	void MouseRelease(Vector2 position);
	void MouseHover(Vector2 position);

	Vector2 GetNowMouseRightClickPoint() { return now_mouse_right_click_point; }
	bool IsDragging();
	void ChangeStateToBuild(int building_type);
	Rect2 GetDragRect();
	bool IsTileHighlighting();
	Rect2 GetTileHighlight();

};