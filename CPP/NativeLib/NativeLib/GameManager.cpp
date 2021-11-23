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

	register_signal<GameManager>(String("create_character"), "ID", GODOT_VARIANT_TYPE_INT);
}

void GameManager::_init(){
}

void GameManager::_ready(){
	NewGame();
	progress_manager.SetGameWorld(&game_world);
	ai_manager.SetGameWorld(&game_world);
}

void GameManager::_process(float delta){
	ai_manager.Update(delta);
	progress_manager.Update(delta);
	FetchQueueAndSignalToGodot();
}

void GameManager::_physics_process(float delta){
}


