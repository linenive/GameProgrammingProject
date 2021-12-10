#pragma once
#include "ControlState.h"

class BuildState : public ControlState {
private:
	StaticUnitService* static_unit_service;
	eBuildingType scheduled_building_type = eBuildingType::SMALL_HOUSE;

	bool CanBuilding(Vector2 mouse_position) {
		if (input.is_building_blueprint_ready) {
			return static_unit_service->IsPlacablePosition((int)scheduled_building_type, mouse_position);
		}
		return false;
	}

	void BuildBuilding(Vector2 mouse_position) {
		int new_building_id = static_unit_service->CreateBuilding((int)scheduled_building_type, mouse_position);
		village_service->DecreaseMoney(static_unit_service->GetBuildingById(new_building_id)->build_cost, mouse_position);
		input.new_building_ids.push(new_building_id);
	}

public:
	BuildState(VillageService* _village_service, TileService* _tile_service,
		StaticUnitService* _static_unit_service)
		: ControlState(_village_service, _tile_service),
		static_unit_service(_static_unit_service) {}

	void MouseHover(Vector2 mouse_position) override {
		HighlightHoverdTile(mouse_position);

		if (input.is_building_blueprint_ready) {
			input.scheduled_building->SetBluePrintPosition(
				ClingToCloseCoordinate(mouse_position)
			);
			if (CanBuilding(mouse_position)) {
				input.is_build_able = true;
			}
			else {
				input.is_build_able = false;
			}
		}
	}

	void MouseClick(Vector2 mouse_position) override {
		if (CanBuilding(mouse_position)) {
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