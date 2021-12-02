#pragma once
#include "Common.h"
#include "GameManager.h"
#include "ControlContextService.h"
#include <Node.hpp>
#include <InputEventMouseButton.hpp>

class InputManager : public Node {
	GODOT_CLASS(InputManager, Node);

private:
	ControlContextService* control_context_service;

	Vector2 now_mouse_point;
	Vector2 now_mouse_right_click_point;
	
	void LoadGameWorld();

	void EmitStateSignalBuilding();
	void EmitStateSignalInstall();
	void EmitStateSignalNormal();
	void EmitBuildSignal(int building_id);
	void EmitStructureSignal(int building_id);
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
	bool IsInstalling();
	Array GetBuildingBluePrint();
	Array GetStructureBluePrint();
	void ChangeStateToBuild(int building_type);
	void ChangeStateToInstall(int structure_type);
	void ChangeStateToNormal();
	Rect2 GetDragRect();
	bool IsTileHighlighting();
	Rect2 GetTileHighlight();
};