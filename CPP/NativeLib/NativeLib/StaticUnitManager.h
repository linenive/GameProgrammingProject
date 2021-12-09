#pragma once

#include "GameManager.h"
#include <Node.hpp>

class StaticUnitManager : public Node {
	GODOT_CLASS(StaticUnitManager, Node);

private:
	StaticUnitService* static_unit_service;
	ResidentService* resident_service;
	void LoadGameWorld();

public:
	static void _register_methods();
	void _ready();
	void _init();

	bool RecruitGuestAsResident(int char_id) {
		return resident_service->RecruitGuestAsResident(char_id);
	}

	void AssignResidentToWorkSpace(int char_id, int building_id) {
		return resident_service->AssignResidentToWorkSpace(char_id, building_id);
	}

	Array GetBuildingInfo(int id) {
		return static_unit_service->GetBuildingInfo(id);
	}

	int GetStructureType(int id) {
		return static_cast<int>(static_unit_service->GetStructureById(id)->type);
	}

	Vector2 GetStructurePosition(int id) {
		return static_unit_service->GetStructureById(id)->GetTopLeftBlockPosition();
	}

	Array GetStructuresInfo() {
		return static_unit_service->GetStructuresInfo();
	}

	Array GetStructureInfo(int id) {
		return static_unit_service->GetStructureInfo(id);
	}
};