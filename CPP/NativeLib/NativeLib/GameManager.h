#pragma once
#include "Common.h"
#include "GameWorld.h"
#include "AIManager.h"
#include "ProgressManager.h"
#include <Node.hpp>

class GameManager : public Node {
	GODOT_CLASS(GameManager, Node);

private:
	GameWorld game_world;
	AIManager ai_manager;
	ProgressManager progress_manager;

	void NewGame();
	void LoadGame();

	//To-do
	void EmitNewCharacter(int character_id) {
		emit_signal(String("create_character"), character_id);
	}
	void FetchQueue() {
		queue<int>* new_character_ids = &(game_world.GetObjectRepository()->new_character_ids);
		while (!new_character_ids->empty()) {
			int new_id = new_character_ids->front();
			new_character_ids->pop();
			EmitNewCharacter(new_id);
		}
	}

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _process(float delta);
	void _physics_process(float delta);

	void AIClickUpdate(Vector2 new_target);
	GameWorld* GetGameWorld() { return &game_world; }
};