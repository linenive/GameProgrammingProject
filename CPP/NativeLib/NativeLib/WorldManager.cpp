#include "WorldManager.h"
#include "GodotScenePath.h"

void WorldManager::_register_methods() {
	register_method("_init", &WorldManager::_init);
	register_method("_ready", &WorldManager::_ready);
	register_method("_process", &WorldManager::_process);

	register_method("GetTileNumber", &WorldManager::GetTileNumber);
	register_method("GetTileTransform", &WorldManager::GetTileTransform);
	register_method("GetTileScale", &WorldManager::GetTileScale);
	register_method("GetTileType", &WorldManager::GetTileType);
	register_method("GetTileName", &WorldManager::GetTileName);

	register_method("TestNewCharacter", &WorldManager::TestNewCharacter);
	register_method("GetCharacterNumber", &WorldManager::GetCharacterNumber);
	register_method("GetCharacterTransform", &WorldManager::GetCharacterTransform);
	register_method("GetCharacterScale", &WorldManager::GetCharacterScale);
	register_method("GetCharacterName", &WorldManager::GetCharacterName);
	register_method("GetCharacterItem", &WorldManager::GetCharacterItem);
	register_method("GetCharacterInventorySize", &WorldManager::GetCharacterInventorySize);

	register_method("GetTileId", &WorldManager::GetTileId);
	register_method("GetWorldSize", &WorldManager::GetWorldSize);

	register_method("GetVillageName", &WorldManager::GetVillageName);
	register_method("SetVillageName", &WorldManager::SetVillageName);
	register_method("GetMoney", &WorldManager::GetMoney);

}

void WorldManager::_init() {

}

void WorldManager::_ready() {
	LoadGameWorld();
}

void WorldManager::_process(float delta)
{

}

int WorldManager::GetTileId(Vector2 vector) {
	return game_world->GetTileMap()->GetTileId(vector);
}

Vector2 WorldManager::GetWorldSize() {
	Vector2 vector = Vector2();
	vector.x = game_world->GetTileMap()->GetTileSizeX() * TILE_WIDTH;
	vector.y = game_world->GetTileMap()->GetTileSizeY() * TILE_HEIGHT;
	return vector;
}

void WorldManager::LoadGameWorld() {
	Node* node = get_node(NodePath(SCENEPATH_GAMEMANAGER.c_str()));
	ERR_FAIL_COND(node == nullptr);
	GameManager* child = node->cast_to<GameManager>(node);
	ERR_FAIL_COND(child == nullptr);
	game_world = child->GetGameWorld();

}

bool WorldManager::CheckCoordinatesInTileMap(Coordinates coord){
	return (
		coord.x > -1 && coord.x < game_world->GetTileMap()->GetTileSizeX() &&
		coord.y > -1 && coord.y < game_world->GetTileMap()->GetTileSizeY()
	);
}
Array WorldManager::GetCharacterItem(int character_id, int item_id) {
	Array result = Array();
	Item item = game_world->GetObjectRepository()->GetCharacter(character_id).GetInventory()->GetItem(item_id);

	result.push_back(item.GetName().c_str());
	result.push_back(item.GetType().c_str());

	return result;
}
