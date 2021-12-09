#pragma once
#include "ControlState.h"
#include "BuildState.h"
#include "InstallState.h"

class ControlContextService {
private:
	ControlState* current_state;
	NormalState* normal_state;
	BuildState* build_state;
	InstallState* install_state;

public:
	ControlContextService(TileService* tile_service, ObjectService* object_service,
		StaticUnitService* static_unit_service, VillageService* village_service) {
		normal_state = new NormalState(village_service, tile_service, object_service, static_unit_service);
		build_state = new BuildState(village_service, tile_service, static_unit_service);
		install_state = new InstallState(village_service, tile_service, static_unit_service);
		current_state = normal_state;
	}
	~ControlContextService() {
		delete normal_state;
		delete build_state;
		delete install_state;
	}

	void SwitchToNormalState() {
		current_state = normal_state;
	}

	void SwitchToBulidState(int building_type) {
		build_state->SetScheduledBuildingType(building_type);
		current_state = build_state;
	}
	void SwitchToInstallState(int structure_type) {
		install_state->SetScheduledStructureType(structure_type);
		current_state = install_state;
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
