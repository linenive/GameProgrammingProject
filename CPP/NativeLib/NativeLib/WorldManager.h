#pragma once
#include "GameManager.h"
#include "ObjectService.h"
#include <Node.hpp>

class WorldManager : public Node {
	GODOT_CLASS(WorldManager, Node);

private:
	GameWorldForWorld* game_world;
	ObjectService *object_service; //주입받기
	void LoadGameWorld();
	bool CheckCoordinatesInTileMap(Coordinates coord);

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _process(float delta);

	Vector2 GetTileCoordinate(Vector2 position) {
		Coordinates coord = game_world->GetTileMap()->GetTileCoordinate(position);
		return Vector2(coord.x, coord.y);
	}

	float GetTilePassSpeed(Vector2 coordinate) {
		return game_world->GetTileMap()->GetTilePassSpeed(coordinate.x, coordinate.y);
	}
	int GetTileSizeX() { return game_world->GetTileMap()->GetTileSizeX(); }
	int GetTileSizeY() { return game_world->GetTileMap()->GetTileSizeY(); }
	Transform2D GetSurfaceTransform(Vector2 coordinate) {
		return game_world->GetTileMap()->GetSurface(coordinate.x, coordinate.y)->GetPhysics()->GetTransform();
	}
	Vector2 GetSurfaceScale(Vector2 coordinate) {
		return game_world->GetTileMap()->GetSurface(coordinate.x, coordinate.y)->GetPhysics()->GetScale();
	}
	int GetSurfaceType(Vector2 coordinate) {
		return (int)game_world->GetTileMap()->GetSurface(coordinate.x, coordinate.y)->GetSurfaceType().type;
	}
	String GetSurfaceName(Vector2 coordinate) {
		return String(game_world->GetTileMap()->GetSurface(coordinate.x, coordinate.y)->GetName().c_str());
	}
	Array GetBlockTypes(Vector2 coordinate);
	void TestNewCharacter(Transform2D transform) {
		object_service->TestNewCharacter(transform);
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