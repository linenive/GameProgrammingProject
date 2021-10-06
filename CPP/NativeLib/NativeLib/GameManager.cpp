#include "GameManager.h"

void GameManager::NewGame() {
	game_world = GameWorld();
}

void GameManager::_register_methods() {
	register_method("_init", &GameManager::_ready);
	register_method("_ready", &GameManager::_ready);
	register_method("_process", &GameManager::_process);
	register_method("_physics_process", &GameManager::_physics_process);

	register_property<GameManager, int>("testAttr", &GameManager::test_attr, 10);
}

void GameManager::_init(){
	
}

void GameManager::_ready(){
}

void GameManager::_process(float delta){
}

void GameManager::_physics_process(float delta){
}


