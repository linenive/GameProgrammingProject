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

	void AssignCharacterToHouse(int char_id, int building_id) {
		resident_service->AssignResidentToHome(char_id, building_id);
	}

	Array GetBuildingInfo(int id) {
		return static_unit_service->GetBuildingInfo(id);
	}
};