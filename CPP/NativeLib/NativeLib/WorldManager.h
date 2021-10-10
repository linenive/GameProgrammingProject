#pragma once
#include "Common.h"
#include "GameManager.h"
#include <Node.hpp>

class WorldManager : public Node {
	GODOT_CLASS(WorldManager, Node);

private:
	GameWorldForWorld* game_world;
	void GetGameWorld();

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _process(float delta);

	int GetTileSize() { return game_world->GetTileMap().GetTileSize(); }
	Transform2D GetTileTransform(int tile_num){
		return game_world->GetTileMap().GetTile(tile_num).GetTransform();
	}
	int GetTileType(int tile_num) {
		return game_world->GetTileMap().GetTile(tile_num).GetTileType();
	}
};