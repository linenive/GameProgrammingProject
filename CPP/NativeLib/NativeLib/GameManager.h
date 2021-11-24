#pragma once
#include "Common.h"
#include "GameService.h"
#include <Node.hpp>

class GameManager : public Node {
	GODOT_CLASS(GameManager, Node);

private:
	GameService game_service;

	void NewGame();
	void LoadGame();

	//To-do
	void EmitNewCharacter(int character_id) {
		emit_signal(String("create_character"), character_id);
	}

	void FetchQueueAndSignalToGodot() {
		queue<int>* new_character_ids = &(game_service.object_service->new_character_ids);
		while (!new_character_ids->empty()) {
			int new_id = new_character_ids->front();
			new_character_ids->pop();
			EmitNewCharacter(new_id);
		}
	}
	/*
	void LetGuestsLeave() {
		queue<Character*>* village_leavers = ai_manager.GetVillageLeavers();
		while (!village_leavers->empty()) {
			
		}
	}*/

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _process(float delta);
	void _physics_process(float delta);

	GameService* GetGameService() { return &game_service; }
};