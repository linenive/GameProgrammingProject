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

	register_method("CheckTileInVector2", &WorldManager::CheckTileInVector2);
	register_method("GetTileIdByVector2", &WorldManager::GetTileIdByVector2);
	register_method("GetWorldSize", &WorldManager::GetWorldSize);
}

void WorldManager::_init() {

}

void WorldManager::_ready() {
	LoadGameWorld();
}

void WorldManager::_process(float delta)
{

}


bool WorldManager::CheckTileInVector2(Vector2 vector){
	float x = vector.x;
	float y = vector.y;
	Coordinates hovered_tile = ApsolutePositionToCoordinates(Vector2(x, y));
	
	return CheckCoordinatesInTileMap(hovered_tile);
}

int WorldManager::GetTileIdByVector2(Vector2 vector) {
	float x = vector.x;
	float y = vector.y;
	Coordinates hovered_tile = ApsolutePositionToCoordinates(Vector2(x, y));
	// printf("[WorldManager]GetTile: %d\n", CalculateTileNumberByCoordinates(hovered_tile));
	return CalculateTileNumberByCoordinates(hovered_tile);
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

int WorldManager::CalculateTileNumberByCoordinates(Coordinates coord)
{
	int tile_size_x = game_world->GetTileMap()->GetTileSizeX();
	return coord.x + tile_size_x * coord.y;
}

bool WorldManager::CheckCoordinatesInTileMap(Coordinates coord)
{
	return (
		coord.x > -1 && coord.x < game_world->GetTileMap()->GetTileSizeX() &&
		coord.y > -1 && coord.y < game_world->GetTileMap()->GetTileSizeY()
	);
}
