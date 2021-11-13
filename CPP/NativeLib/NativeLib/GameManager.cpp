#include "GameManager.h"
#include "SkillService.h"

void GameManager::NewGame() {
	game_world = GameWorld();
}

void GameManager::_register_methods() {
	register_method("_init", &GameManager::_init);
	register_method("_ready", &GameManager::_ready);
	register_method("_process", &GameManager::_process);
	register_method("_physics_process", &GameManager::_physics_process);
}

void GameManager::_init(){
}

void GameManager::_ready(){
	NewGame();
	ai_manager.SetGameWorld(&game_world);
	progress_manager.SetGameWorld(&game_world);
}

void GameManager::_process(float delta){
	ai_manager.Update(delta);
	progress_manager.Update(delta);
}

void GameManager::_physics_process(float delta){
}


