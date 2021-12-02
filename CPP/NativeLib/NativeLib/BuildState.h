#pragma once
#include "ControlState.h"

class BuildState : public ControlState {
private:
	StaticUnitService* static_unit_service;
	eBuildingType scheduled_building_type = eBuildingType::SMALL_HOUSE;

	void HighlightHoverdTile(Vector2 mouse_position) {
		Coordinates hovered_tile_coord = GetTile(mouse_position);
		if (hovered_tile_coord.x >= 0) {
			Surface* hoverd_surface = tile_repo->GetSurface(hovered_tile_coord);
		}
		else {
		}
	}

	bool CanBuiding(Vector2 mouse_position) {
		if (input.is_building_blueprint_ready) {
			return static_unit_service->IsPlacablePosition((int)scheduled_building_type, mouse_position);
		}
		return false;
	}

	void BuildBuilding(Vector2 mouse_position) {
		int new_building_id = static_unit_service->CreateBuilding((int)scheduled_building_type, mouse_position);
		input.new_building_ids.push(new_building_id);
	}

public:
	BuildState(TileRepository* t_repo, StaticUnitService* _static_unit_service)
		: ControlState(t_repo), static_unit_service(_static_unit_service) {}

	void MouseHover(Vector2 mouse_position) override {
		HighlightHoverdTile(mouse_position);

		if (input.is_building_blueprint_ready) {
			input.scheduled_building->SetBluePrintPosition(
				ClingToCloseCoordinate(mouse_position)
			);
		}
	}

	void MouseClick(Vector2 mouse_position) override {
		if (CanBuiding(mouse_position)) {
			BuildBuilding(mouse_position);
		}
	}

	void MouseRelease(Vector2 mouse_position) override {
	}

	void SetScheduledBuildingType(int building_type) {
		scheduled_building_type = (eBuildingType)building_type;
		input.scheduled_building = static_unit_service->CreateBluePrintBuilding(building_type);
		input.is_building_blueprint_ready = true;
	}
};