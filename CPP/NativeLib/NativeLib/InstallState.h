#pragma once
#include "ControlState.h"

class InstallState : public ControlState {
private:
	StaticUnitService* static_unit_service;
	eStructureType scheduled_structure_type = eStructureType::SINGLE_BED;

	bool CanInstalling(Vector2 mouse_position) {
		if (input.is_structure_blueprint_ready) {
			return static_unit_service->IsStructurePlacablePosition((int)scheduled_structure_type, mouse_position);
		}
		return false;
	}

	void InstallStructure(Vector2 mouse_position) {
		int new_structure_id = static_unit_service->CreateStructure((int)scheduled_structure_type, mouse_position);
		village_service->DecreaseMoney(static_unit_service->GetStructureById(new_structure_id)->build_cost);
		input.new_structure_ids.push(new_structure_id);
	}
public:
	InstallState(VillageService* _village_service, TileService* _tile_service,
		StaticUnitService* _static_unit_service)
		: ControlState(_village_service, _tile_service),
		static_unit_service(_static_unit_service) {}

	void MouseHover(Vector2 mouse_position) override {
		// HighlightHoverdTile(mouse_position);

		if (input.is_structure_blueprint_ready) {
			input.scheduled_structure->SetBluePrintPosition(
				ClingToCloseCoordinate(mouse_position)
			);
		}
	}

	void MouseClick(Vector2 mouse_position) override {
		Godot::print("[InstallState]Mouse Click: " + mouse_position);
		if (CanInstalling(mouse_position)) {
			InstallStructure(mouse_position);
		}
	}

	void MouseRelease(Vector2 mouse_position) override {
		Godot::print("[InstallState]Mouse Release: " + mouse_position);
	}

	void SetScheduledStructureType(int structure_type) {
		scheduled_structure_type = (eStructureType)structure_type;
		input.scheduled_structure = static_unit_service->CreateBluePrintStructure(structure_type);
		input.is_structure_blueprint_ready = true;
	}
};
