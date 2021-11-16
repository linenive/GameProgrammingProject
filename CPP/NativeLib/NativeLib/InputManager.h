#pragma once
#include "Common.h"
#include "GameManager.h"
#include "ControlState.h"
#include "StaticUnitService.h"
#include "GameWorldForStaticUnit.h"
#include <Node.hpp>
#include <InputEventMouseButton.hpp>

class InputManager : public Node {
	GODOT_CLASS(InputManager, Node);

private:
	ControlContext* control_context;
	StaticUnitService static_unit_service;
	GameWorldForInput* game_world;
	Vector2 now_mouse_point;
	Vector2 now_mouse_right_click_point;

	void LoadGameWorld();

public:
	~InputManager() {
		delete control_context;
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
	bool IsBuilding();
	Array GetBuildingBluePrint() {
		Array block_array = Array();
		Building* scheduled_building = control_context->GetInputStatus().scheduled_building;

		for (Block* b : scheduled_building->blocks) {
			Array arr = Array();
			arr.append(String(b->GetName().c_str()));
			arr.append(b->GetPhysics().GetPosition());
			block_array.push_back(arr);
		}

		return block_array;
	}
	void ChangeStateToBuild(int building_type);
	Rect2 GetDragRect();
	bool IsTileHighlighting();
	Rect2 GetTileHighlight();

};