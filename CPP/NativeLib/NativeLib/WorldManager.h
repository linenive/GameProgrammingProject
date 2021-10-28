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
		return game_world->GetTileMap()->GetTile(tile_id).GetPhysics().getTransform();
	}
	Vector2 GetTileScale(int tile_id) {
		return game_world->GetTileMap()->GetTile(tile_id).GetScale();
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
	Transform2D GetCharacterTransform(int character_id) {
		return game_world->GetObjectRepository()->GetCharacter(character_id).GetPhysics().getTransform();
	}
	Vector2 GetCharacterScale(int character_id) {
		return game_world->GetObjectRepository()->GetCharacter(character_id).GetScale();
	}
	String GetCharacterName(int character_id) {
		return String(game_world->GetObjectRepository()->GetCharacter(character_id).GetName().c_str());
	}
	Dictionary GetCharacterInfo(int character_id);

	Array GetCharacterItem(int character_id, int item_id);

	int GetCharacterInventorySize(int character_id) {
		return game_world->GetObjectRepository()->GetCharacter(character_id).GetInventory()->GetSize();
	}

	bool CheckTileInVector2(Vector2 vector);
	int GetTileIdByVector2(Vector2 vector);

	Vector2 GetWorldSize();

	String GetVillageName() {
		return String(game_world->GetVillageRepository()->GetVillage()->GetVillageName().c_str());
	}

	void SetVillageName(String new_name) {
		game_world->GetVillageRepository()->GetVillage()->SetVillageName(new_name.utf8().get_data());
	}

	int GetMoney() {
		return game_world->GetVillageRepository()->GetVillage()->GetMoney();
	}
};