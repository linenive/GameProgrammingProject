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

	void EmitDeleteStructure(int id) {
		emit_signal(String("delete_structrue"), id);
	}

	void FetchQueueAndSignal() {
		queue<int>* deleted_structure_ids = &(static_unit_service->deleted_structure_ids);
		while (!deleted_structure_ids->empty()) {
			int deleted_id = deleted_structure_ids->front();
			deleted_structure_ids->pop();
			EmitDeleteStructure(deleted_id);
		}
	}
};