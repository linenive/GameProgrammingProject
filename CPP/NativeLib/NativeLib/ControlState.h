#pragma once
#include <queue>
#include "StaticUnitService.h"
#include "CoordinatesSystem.h"

class InputStatus {
public:
	~InputStatus() {
		delete scheduled_building;
	}
	Building* scheduled_building;
	bool is_dragging = false;
	Vector2 drag_start_point;
	Vector2 now_mouse_point;
	bool is_area_highlighted = false;
	Rect2 highlighted_area;
	bool is_building = false;

	queue<int> new_building_ids;


	void ResetDrag() {
		is_dragging = false;
		drag_start_point = Vector2(0, 0);
	}
};

class ControlState {
protected:
	InputStatus input;
	GameWorldForInput* world;

	void StartDrag(Vector2 start_pos) {
		input.drag_start_point = start_pos;
		input.is_dragging = true;
	}

	void EndDrag(Vector2 end_pos) {
		input.is_dragging = false;
	}

	Coordinates GetTileCoordMouseHoveredTileMap(Vector2 mouse_position) {
		return world->GetTileMap()->GetTileCoordinate(mouse_position);
	}

public:
	ControlState(GameWorldForInput* _world) : world(_world) {}
	virtual void MouseHover(Vector2 position) = 0;
	virtual void MouseClick(Vector2 position) = 0;
	virtual void MouseRelease(Vector2 position) = 0;
	void SetGameWorld(GameWorldForInput* _world) { world = _world; }
	InputStatus* GetInputStatus() { return &input; }
};

class NormalState : public ControlState {
public:
	NormalState(GameWorldForInput* _world) : ControlState(_world) {}

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

class BuildState : public ControlState {
private:
	StaticUnitService* static_unit_service;
	eBuildingType scheduled_building_type = eBuildingType::SMALL_HOUSE;

	void HighlightHoverdTile(Vector2 mouse_position) {
		Coordinates hovered_tile_coord = GetTileCoordMouseHoveredTileMap(mouse_position);
		if (hovered_tile_coord.x >= 0) {
			Surface* hoverd_surface = world->GetTileMap()->GetSurface(hovered_tile_coord);
		}
		else {
		}
	}

	bool CanBuiding(Vector2 mouse_position) {
		if (input.is_building) {
			return static_unit_service->IsPlacablePosition((int)scheduled_building_type, mouse_position);
		}
		return false;
	}

	void BuildBuilding(Vector2 mouse_position) {
		int new_building_id;
		new_building_id = static_unit_service->CreateBuilding((int)scheduled_building_type, mouse_position);
		input.new_building_ids.push(new_building_id);
	}

public:
	BuildState(GameWorldForInput* _world, StaticUnitService* _static_unit_service)
		: ControlState(_world), static_unit_service(_static_unit_service) {}

	void MouseHover(Vector2 mouse_position) override {
		HighlightHoverdTile(mouse_position);

		if (input.is_building) {
			input.scheduled_building->SetBluePrintPosition(
				ClingToCloseCoordinate(mouse_position)
			);
		}
	}

	void MouseClick(Vector2 mouse_position) override {
		if (CanBuiding(mouse_position)) {
			BuildBuilding(mouse_position);
		}
		Godot::print("[BuildState]Mouse Click: " + mouse_position);
	}

	void MouseRelease(Vector2 mouse_position) override {
		Godot::print("[BuildState]Mouse Release: " + mouse_position);
	}

	void SetScheduledBuildingType(int building_type) {
		scheduled_building_type = (eBuildingType)building_type;
		input.scheduled_building = static_unit_service->CreateBluePrintBuilding(building_type);
		input.is_building = true;
	}
};

class InstallState : public ControlState {
private:
	void HighlightHoverdTile(Vector2 mouse_position) {
		Coordinates hovered_tile_coord = GetTileCoordMouseHoveredTileMap(mouse_position);
		if (hovered_tile_coord.x >= 0) {
			Surface* hoverd_surface = world->GetTileMap()->GetSurface(hovered_tile_coord);
			input.is_area_highlighted = true;
			input.highlighted_area = hoverd_surface->GetPhysics()->GetRect();
		}
		else {
			input.is_area_highlighted = false;
		}
	}
public:
	InstallState(GameWorldForInput* _world) : ControlState(_world) {}

	void MouseHover(Vector2 mouse_position) override {
		HighlightHoverdTile(mouse_position);
	}

	void MouseClick(Vector2 mouse_position) override {
		Godot::print("[InstallState]Mouse Click: " + mouse_position);
	}

	void MouseRelease(Vector2 mouse_position) override {
		Godot::print("[InstallState]Mouse Release: " + mouse_position);
	}
};

class ControlContext {
private:
	ControlState* current_state;
	NormalState* normal_state;
	BuildState* build_state;

public:
	ControlContext(GameWorldForInput* world, StaticUnitService* static_unit_service) {
		normal_state = new NormalState(world);
		build_state = new BuildState(world, static_unit_service);
		current_state = normal_state;
	}
	~ControlContext() {
		delete normal_state;
		delete build_state;
	}

	void SwitchToNormalState() {
		current_state = normal_state;
	}

	void SwitchToBulidState(int building_type) {
		build_state->SetScheduledBuildingType(building_type);
		current_state = build_state;
	}

	void MouseHover(Vector2 mouse_position) {
		current_state->MouseHover(mouse_position);
	}

	void MouseClick(Vector2 mouse_position) {
		current_state->MouseClick(mouse_position);
	}

	void MouseRelease(Vector2 mouse_position) {
		current_state->MouseRelease(mouse_position);
	}

	InputStatus* GetInputStatus() {
		return current_state->GetInputStatus();
	}
};
