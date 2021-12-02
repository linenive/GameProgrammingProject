#pragma once
#include "ControlState.h"

class InstallState : public ControlState {
private:
	StaticUnitService* static_unit_service;
	eStructureType scheduled_structure_type = eStructureType::SINGLE_BED;

	void HighlightHoverdTile(Vector2 mouse_position) {
		Coordinates hovered_tile_coord = GetTile(mouse_position);
		if (hovered_tile_coord.x >= 0) {
			Surface* hoverd_surface = tile_repo->GetSurface(hovered_tile_coord);
			input.is_area_highlighted = true;
			input.highlighted_area = hoverd_surface->GetPhysics()->GetRect();
		}
		else {
			input.is_area_highlighted = false;
		}
	}

	bool CanInstalling(Vector2 mouse_position) {
		if (input.is_structure_blueprint_ready) {
			return static_unit_service->IsStructurePlacablePosition((int)scheduled_structure_type, mouse_position);
		}
		return false;
	}

	void InstallStructure(Vector2 mouse_position) {
		int new_structure_id = static_unit_service->CreateStructure((int)scheduled_structure_type, mouse_position);
		input.new_structure_ids.push(new_structure_id);
	}
public:
	InstallState(TileRepository* t_repo, StaticUnitService* _static_unit_service)
		: ControlState(t_repo), static_unit_service(_static_unit_service) {}

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
