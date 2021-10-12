#pragma once
#include "Common.h"
#include "GameManager.h"
#include <Node.hpp>
#include "CoordinatesSystem.h"

class WorldManager : public Node {
	GODOT_CLASS(WorldManager, Node);

private:
	GameWorldForWorld* game_world;
	void LoadGameWorld();
	int CalculateTileNumberByCoordinates(Coordinates coord);
	bool CheckCoordinatesInTileMap(Coordinates coord);

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _process(float delta);

	int GetTileNumber() { return game_world->GetTileMap()->GetTileSize(); }
	Transform2D GetTileTransform(int tile_id){
		return game_world->GetTileMap()->GetTile(tile_id).GetTransform();
	}
	int GetTileType(int tile_id) {
		return (int) game_world->GetTileMap()->GetTile(tile_id).GetTileType().type;
	}
	String GetTileName(int tile_id) {
		return String(game_world->GetTileMap()->GetTile(tile_id).GetName().c_str());
	}
	void TestNewCharacter(Transform2D transform) {
		game_world->GetObjectRepository()->TestNewCharacter(transform);
	}
	int GetCharacterNumber() {
		return game_world->GetObjectRepository()->GetCharacterNumber();
	}
	Transform2D GetCharacterTransform(int i) {
		return game_world->GetObjectRepository()->GetCharacterTransform(i);
	}
	bool CheckTileInVector2(Vector2 vector);
	int GetTileIdByVector2(Vector2 vector);

	Vector2 GetWorldSize();
};