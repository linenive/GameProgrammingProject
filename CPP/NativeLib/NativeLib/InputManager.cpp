#include "InputManager.h"
#include "GodotScenePath.h"

void InputManager::_register_methods() {
	register_method("_init", &InputManager::_init);
	register_method("_ready", &InputManager::_ready);
	register_method("_process", &InputManager::_process);
}

void InputManager::_init() {

}

void InputManager::_ready() {
	InputManager();
}

void InputManager::_process(float delta)
{

}

void InputManager::LoadGameWorld() {
	Node* node = get_node(NodePath(SCENEPATH_GAMEMANAGER.c_str()));
	ERR_FAIL_COND(node == nullptr);
	GameManager* child = node->cast_to<GameManager>(node);
	ERR_FAIL_COND(child == nullptr);
	game_world = child->GetGameWorld();

}