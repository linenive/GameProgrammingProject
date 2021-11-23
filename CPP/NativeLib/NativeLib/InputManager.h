#pragma once
#include "Common.h"
#include "GameManager.h"
#include "StaticUnitService.h"
#include <Node.hpp>
#include <InputEventMouseButton.hpp>

class InputManager : public Node {
	GODOT_CLASS(InputManager, Node);

private:
	ControlContext* control_context;

	Vector2 now_mouse_point;
	Vector2 now_mouse_right_click_point;
	
	void LoadGameWorld();

	void EmitStateSignalBuilding();
	void EmitStateSignalNormal();
	void EmitBuildSignal(int building_id);
	void FetchInputQueue();

public:
	
	static void _register_methods();
	void _init();
	void _ready();
	void _process(float delta);

	void MouseClick(Vector2 position);
	void MouseRightClick(Vector2 position);
	void MouseRelease(Vector2 position);
	void MouseHover(Vector2 position);

	Vector2 GetNowMouseRightClickPoint() { return now_mouse_right_click_point; }
	bool IsDragging();
	bool IsBuilding();
	Array GetBuildingBluePrint();
	void ChangeStateToBuild(int building_type);
	void ChangeStateToNormal();
	Rect2 GetDragRect();
	bool IsTileHighlighting();
	Rect2 GetTileHighlight();
};