#pragma once
#include "Common.h"
#include "GameManager.h"
#include <Node.hpp>
#include <InputEventMouseButton.hpp>

class InputManager : public Node {
	GODOT_CLASS(InputManager, Node);

private:
	GameWorldForInput* game_world;
	bool is_dragging;
	Vector2 drag_start_point;
	Vector2 now_mouse_point;
	Vector2 now_mouse_right_click_point;

	void LoadGameWorld();
	void StartDrag(Vector2 start_pos);
	void EndDrag(Vector2 end_pos);

public:
	static void _register_methods();
	void _init();
	void _ready();
	void MouseClick(Vector2 position);
	void MouseRightClick(Vector2 position);
	void MouseRelease(Vector2 position);
	void MouseHover(Vector2 position);

	Vector2 GetNowMouseRightClickPoint() { return now_mouse_right_click_point; }
	bool IsDragging();
	Rect2 GetDragRect();

};