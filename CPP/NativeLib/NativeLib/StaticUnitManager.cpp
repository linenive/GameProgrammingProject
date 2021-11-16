#include "StaticUnitManager.h"
#include "GodotScenePath.h"

void StaticUnitManager::_register_methods() {
	register_method("_init", &StaticUnitManager::_init);
	register_method("_ready", &StaticUnitManager::_ready);

	register_method("CreateBuilding", &StaticUnitManager::CreateBuilding);
	register_method("IsPlacablePosition", &StaticUnitManager::IsPlacablePosition);
	register_method("DeleteBuildingById", &StaticUnitManager::DeleteBuildingById);
	register_method("GetUpdateTileList", &StaticUnitManager::GetUpdateTileList);
}

void StaticUnitManager::_init() {
}

void StaticUnitManager::_ready() {
	LoadGameWorld();
}

void StaticUnitManager::LoadGameWorld() {
	Node* node = get_node(NodePath(String(SCENEPATH_GAMEMANAGER.c_str())));
	ERR_FAIL_COND(node == nullptr);
	GameManager* child = node->cast_to<GameManager>(node);
	ERR_FAIL_COND(child == nullptr);
	game_world = child->GetGameWorld();
}