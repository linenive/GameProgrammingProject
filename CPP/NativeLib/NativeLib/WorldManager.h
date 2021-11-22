#pragma once
#include "GameManager.h"
#include <Node.hpp>

class WorldManager : public Node {
	GODOT_CLASS(WorldManager, Node);

private:
	GameWorldForWorld* game_world;
	void LoadGameWorld();
	bool CheckCoordinatesInTileMap(Coordinates coord);

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _process(float delta);

	int GetTileNumber() { return game_world->GetTileMap()->GetTileSize(); }
	Transform2D GetSurfaceTransform(int tile_id) {
		return game_world->GetTileMap()->GetSurface(tile_id)->GetPhysics()->GetTransform();
	}
	Vector2 GetSurfaceScale(int tile_id) {
		return game_world->GetTileMap()->GetSurface(tile_id)->GetPhysics()->GetScale();
	}
	int GetSurfaceType(int tile_id) {
		return (int)game_world->GetTileMap()->GetSurface(tile_id)->GetSurfaceType().type;
	}
	String GetSurfaceName(int tile_id) {
		return String(game_world->GetTileMap()->GetSurface(tile_id)->GetName().c_str());
	}
	Array GetBlockTypes(int tile_id);
	void TestNewCharacter(Transform2D transform) {
		game_world->GetObjectRepository()->TestNewCharacter(transform);
	}
	int GetCharacterNumber() {
		return game_world->GetObjectRepository()->GetCharacterNumber();
	}
	Transform2D GetCharacterTransform(int character_id) {
		return game_world->GetObjectRepository()->GetCharacter(character_id)->GetPhysics()->GetTransform();
	}
	Vector2 GetCharacterScale(int character_id) {
		return game_world->GetObjectRepository()->GetCharacter(character_id)->GetPhysics()->GetScale();
	}
	String GetCharacterName(int character_id) {
		return String(game_world->GetObjectRepository()->GetCharacter(character_id)->GetName().c_str());
	}
	Dictionary GetCharacterInfo(int character_id);

	Array GetCharacterItem(int character_id, int item_id);

	int GetCharacterInventorySize(int character_id) {
		return game_world->GetObjectRepository()->GetCharacter(character_id)->GetInventory()->GetSize();
	}

	int GetTileId(Vector2 vector);

	bool CheckTileInVector2(Vector2 vector);
	int GetTileIdByVector2(Vector2 vector);
	int CalculateTileNumberByCoordinates(Coordinates coord);

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