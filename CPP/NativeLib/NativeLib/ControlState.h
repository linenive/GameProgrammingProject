#pragma once

#include <queue>
#include "StaticUnitService.h"
#include "VillageService.h"
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

	queue<int> clicked_character_ids;
	queue<int> clicked_structure_ids;
	queue<int> clicked_building_ids;

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
	VillageService* village_service;
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
	ControlState(VillageService* _village_service, TileService* _tile_service)
		: village_service(_village_service), tile_service(_tile_service) {}
	virtual void MouseHover(Vector2 position) = 0;
	virtual void MouseClick(Vector2 position) = 0;
	virtual void MouseRelease(Vector2 position) = 0;
	InputStatus* GetInputStatus() { return &input; }
};

class NormalState : public ControlState {
private:
	ObjectService* object_service;
	StaticUnitService* static_unit_service;

	void ClickWorldObject(Vector2 position) {
		int clicked_character_id = object_service->GetCharacterId(position);
		if (clicked_character_id != -1) {
			input.clicked_character_ids.push(clicked_character_id);
			return;
		}

		int clicked_structure_id = static_unit_service->GetStructureId(position);
		if (clicked_structure_id != -1) {
			input.clicked_structure_ids.push(clicked_structure_id);
			return;
		}

		int clicked_building_id = static_unit_service->GetBuildingId(position);
		if (clicked_building_id != -1) {
			input.clicked_building_ids.push(clicked_building_id);
			return;
		}
	}

public:
	NormalState(VillageService* _village_service, TileService* tile_service, ObjectService* _object_service,
		StaticUnitService* _static_unit_service)
		: ControlState(_village_service, tile_service),
		object_service(_object_service), static_unit_service(_static_unit_service){}

	void MouseHover(Vector2 mouse_position) override {
	}

	void MouseClick(Vector2 mouse_position) override {
		ClickWorldObject(mouse_position);

		StartDrag(mouse_position);
	}

	void MouseRelease(Vector2 mouse_position) override {
		EndDrag(mouse_position);
	}
};
