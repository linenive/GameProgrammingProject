#pragma once

#include <queue>
#include "StaticUnitService.h"
#include "CoordinatesSystem.h"
#include "TileRepository.h"

class InputStatus {
public:
	~InputStatus() {
		delete scheduled_building;
	}
	Building* scheduled_building;
	Structure* scheduled_structure;
	bool is_dragging = false;
	Vector2 drag_start_point;
	Vector2 now_mouse_point;
	bool is_area_highlighted = false;
	Rect2 highlighted_area;
	bool is_building_blueprint_ready = false;
	bool is_structure_blueprint_ready = false;

	queue<int> new_building_ids;
	queue<int> new_structure_ids;

	void ResetDrag() {
		is_dragging = false;
		drag_start_point = Vector2(0, 0);
	}
};

class ControlState {
protected:
	InputStatus input;
	TileRepository* tile_repo;

	void StartDrag(Vector2 start_pos) {
		input.drag_start_point = start_pos;
		input.is_dragging = true;
	}

	void EndDrag(Vector2 end_pos) {
		input.is_dragging = false;
	}

	Coordinates GetTile(Vector2 mouse_position) {
		return tile_repo->GetTileCoordinate(mouse_position);
	}

public:
	ControlState(TileRepository* t_repo) : tile_repo(t_repo) {}
	virtual void MouseHover(Vector2 position) = 0;
	virtual void MouseClick(Vector2 position) = 0;
	virtual void MouseRelease(Vector2 position) = 0;
	InputStatus* GetInputStatus() { return &input; }
};

class NormalState : public ControlState {
public:
	NormalState(TileRepository* t_repo) : ControlState(t_repo) {}

	void MouseHover(Vector2 mouse_position) override {
	}

	void MouseClick(Vector2 mouse_position) override {
		Godot::print("[NormalState]Mouse Click: " + mouse_position);
		StartDrag(mouse_position);
	}

	void MouseRelease(Vector2 mouse_position) override {
		Godot::print("[NormalState]Mouse Release: " + mouse_position);
		EndDrag(mouse_position);
	}
};
