#pragma once
#include "GameManager.h"
#include <Node.hpp>

class WorldManager : public Node {
	GODOT_CLASS(WorldManager, Node);

private:
	ObjectService* object_service;
	TileService* tile_service;
	VillageService* village_service;
	void LoadGameWorld();

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _process(float delta);

	Vector2 GetTileCoordinate(Vector2 position) {
		return tile_service->GetTileCoordinate(position);
	}

	float GetTilePassSpeed(Vector2 coordinate) {
		return tile_service->GetTilePassSpeed(coordinate.x, coordinate.y);
	}
	int GetTileSizeX() { return tile_service->GetTileSizeX(); }
	int GetTileSizeY() { return tile_service->GetTileSizeY(); }
	Transform2D GetSurfaceTransform(Vector2 coordinate) {
		return tile_service->GetSurface(coordinate.x, coordinate.y)->GetPhysics()->GetTransform();
	}
	Vector2 GetSurfaceScale(Vector2 coordinate) {
		return tile_service->GetSurface(coordinate.x, coordinate.y)->GetPhysics()->GetScale();
	}
	int GetSurfaceType(Vector2 coordinate) {
		return (int)tile_service->GetSurface(coordinate.x, coordinate.y)->GetSurfaceType().type;
	}
	String GetSurfaceName(Vector2 coordinate) {
		return String(tile_service->GetSurface(coordinate.x, coordinate.y)->GetName().c_str());
	}

	Array GetBlockTypes(Vector2 coordinate);

	void TestNewCharacter(Transform2D transform) {
		object_service->TestNewCharacter(transform);
	}
	int GetCharacterNumber() {
		return object_service->GetCharacterNumber();
	}
	Transform2D GetCharacterTransform(int character_id) {
		return object_service->GetCharacter(character_id)->GetPhysics()->GetTransform();
	}
	Vector2 GetCharacterScale(int character_id) {
		return object_service->GetCharacter(character_id)->GetPhysics()->GetScale();
	}
	String GetCharacterName(int character_id) {
		return String(object_service->GetCharacter(character_id)->GetName().c_str());
	}

	Array GetCharacterItem(int character_id, int item_id);

	int GetCharacterInventorySize(int character_id) {
		return object_service->GetCharacter(character_id)->GetInventory()->GetSize();
	}

	Vector2 GetWorldSize();

	String GetVillageName() {
		return String(village_service->GetVillageName());
	}

	void SetVillageName(String new_name) {
		village_service->SetVillageName(new_name);
	}

	int GetMoney() {
		return village_service->GetMoney();
	}
};