#include "GameManager.h"
#include "SkillService.h"

void GameManager::NewGame() {
	
}

void GameManager::_register_methods() {
	register_method("_init", &GameManager::_init);
	register_method("_ready", &GameManager::_ready);
	register_method("_process", &GameManager::_process);
	register_method("_physics_process", &GameManager::_physics_process);

	register_signal<GameManager>(String("create_character"), "ID", GODOT_VARIANT_TYPE_INT);
	register_signal<GameManager>(String("delete_character"), "ID", GODOT_VARIANT_TYPE_INT);
}

void GameManager::_init(){
}

void GameManager::_ready(){
	NewGame();
}

void GameManager::_process(float delta){
	game_service.ai_service->Update(delta);
	game_service.progress_service->Update(delta);
	FetchQueueAndSignalToGodot();
}

void GameManager::_physics_process(float delta){
}


