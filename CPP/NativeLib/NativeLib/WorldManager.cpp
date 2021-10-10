#include "WorldManager.h"
#include "GodotScenePath.h"

void WorldManager::_register_methods() {
	register_method("_init", &WorldManager::_init);
	register_method("_ready", &WorldManager::_ready);
	register_method("_process", &WorldManager::_process);
	register_method("GetTileNumber", &WorldManager::GetTileNumber);
	register_method("GetTileTransform", &WorldManager::GetTileTransform);
	register_method("GetTileType", &WorldManager::GetTileType);
	register_method("TestNewCharacter", &WorldManager::TestNewCharacter);
	register_method("GetCharacterNumber", &WorldManager::GetCharacterNumber);
	register_method("GetCharacterTransform", &WorldManager::GetCharacterTransform);
}

void WorldManager::_init() {

}

void WorldManager::_ready() {
	LoadGameWorld();
}

void WorldManager::_process(float delta)
{

}

void WorldManager::LoadGameWorld() {
	Node* node = get_node(NodePath(SCENEPATH_GAMEMANAGER.c_str()));
	ERR_FAIL_COND(node == nullptr);
	GameManager* child = node->cast_to<GameManager>(node);
	ERR_FAIL_COND(child == nullptr);
	game_world = child->GetGameWorld();

}