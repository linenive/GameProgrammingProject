#pragma once
#include "Common.h"
#include "GameManager.h"
#include <Node.hpp>

class WorldManager : public Node {
	GODOT_CLASS(WorldManager, Node);

private:
	GameWorldForWorld* game_world;
	void LoadGameWorld();

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _process(float delta);

	int GetTileNumber() { return game_world->GetTileMap()->GetTileSize(); }
	Transform2D GetTileTransform(int tile_num){
		return game_world->GetTileMap()->GetTile(tile_num).GetTransform();
	}
	int GetTileType(int tile_num) {
		return game_world->GetTileMap()->GetTile(tile_num).GetTileType();
	}
	void TestNewCharacter(Transform2D transform) {
		game_world->GetObjectRepository()->TestNewCharacter(transform);
	}
	int GetCharacterNumber() {
		return game_world->GetObjectRepository()->GetCharacterNumber();
	}
	void SetNumber() {
		game_world->GetObjectRepository()->SetNumber();
	}
	Transform2D GetCharacterTransform(int i) {
		return game_world->GetObjectRepository()->GetCharacterTransform(i);
	}
};