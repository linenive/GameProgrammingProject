#include "WorldManager.h"
#include "GodotScenePath.h"

void WorldManager::_register_methods() {
	register_method("_init", &WorldManager::_init);
	register_method("_ready", &WorldManager::_ready);
	register_method("_process", &WorldManager::_process);
	register_method("GetTileSize", &WorldManager::GetTileSize);
	register_method("GetTileTransform", &WorldManager::GetTileTransform);
}

void WorldManager::_init() {

}

void WorldManager::_ready() {
	GetGameWorld();
}

void WorldManager::_process(float delta)
{

}

void WorldManager::GetGameWorld() {
	Node* node = get_node(NodePath(SCENEPATH_GAMEMANAGER.c_str()));
	ERR_FAIL_COND(node == nullptr);
	GameManager* child = node->cast_to<GameManager>(node);
	ERR_FAIL_COND(child == nullptr);
	if (node != NULL) {
		game_world = child->GetGameWorld();
	}
}