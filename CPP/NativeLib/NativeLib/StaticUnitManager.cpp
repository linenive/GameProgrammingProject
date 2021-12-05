#include "StaticUnitManager.h"
#include "GodotScenePath.h"

void StaticUnitManager::_register_methods() {
	register_method("RecruitGuestAsResident", &StaticUnitManager::RecruitGuestAsResident);
	register_method("GetBuildingInfo", &StaticUnitManager::GetBuildingInfo);
	register_method("_ready", &StaticUnitManager::_ready);
	register_method("_init", &StaticUnitManager::_init);

	register_method("GetStructureType", &StaticUnitManager::GetStructureType);
	register_method("GetStructurePosition", &StaticUnitManager::GetStructurePosition);
	register_method("GetStructuresInfo", &StaticUnitManager::GetStructuresInfo);
}

void StaticUnitManager::_ready() {
	LoadGameWorld();
	printf("init!\n");
}

void StaticUnitManager::_init() {

}

void StaticUnitManager::LoadGameWorld() {
	Node* node = get_node(NodePath(SCENEPATH_GAMEMANAGER.c_str()));
	ERR_FAIL_COND(node == nullptr);
	GameManager* child = node->cast_to<GameManager>(node);
	ERR_FAIL_COND(child == nullptr);
	resident_service = child->GetGameService()->resident_service;
	static_unit_service = child->GetGameService()->static_unit_service;
}