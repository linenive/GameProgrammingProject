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
	TileService* tile_service;

	void HighlightHoverdTile(Vector2 mouse_position) {
		Coordinates hovered_tile_coord = tile_service->GetTileCoordinate(mouse_position);
		if (hovered_tile_coord.x >= 0) {
			Surface* hoverd_surface = tile_service->GetSurface(hovered_tile_coord);
			input.is_area_highlighted = true;
			input.highlighted_area = hoverd_surface->GetPhysics()->GetRect();
		}
		else {
			input.is_area_highlighted = false;
		}
	}

	void StartDrag(Vector2 start_pos) {
		input.drag_start_point = start_pos;
		input.is_dragging = true;
	}

	void EndDrag(Vector2 end_pos) {
		input.is_dragging = false;
	}

	Coordinates GetTile(Vector2 mouse_position) {
		return tile_service->GetTileCoordinate(mouse_position);
	}

public:
	ControlState(TileService* _tile_service) : tile_service(_tile_service) {}
	virtual void MouseHover(Vector2 position) = 0;
	virtual void MouseClick(Vector2 position) = 0;
	virtual void MouseRelease(Vector2 position) = 0;
	InputStatus* GetInputStatus() { return &input; }
};

class NormalState : public ControlState {
public:
	NormalState(TileService* tile_service) : ControlState(tile_service) {}

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
