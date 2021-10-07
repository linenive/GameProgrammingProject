#include "UIManager.h"
#include "ScenePath.h"

void UIManager::_register_methods() {
	register_method("_init", &UIManager::_init);
	register_method("_ready", &UIManager::_ready);
	register_method("_process", &UIManager::_process);
	register_method("GetYear", &UIManager::GetYear);
	register_method("GetMonth", &UIManager::GetMonth);
	register_method("GetDay", &UIManager::GetDay);
	register_method("GetHour", &UIManager::GetHour);
	register_method("GetMinute", &UIManager::GetMinute);
	register_method("TestFunc", &UIManager::TestFunc);
}

void UIManager::_init(){
	
}

void UIManager::_ready() {
	GetGameWorld();
}

void UIManager::_process(float delta)
{
	
}

void UIManager::GetGameWorld() {
	Node* node = get_node(NodePath(SCENEPATH_GAMEMANAGER));
	ERR_FAIL_COND(node == nullptr);
	GameManager* child = node->cast_to<GameManager>(node);
	ERR_FAIL_COND(child == nullptr);
	if (node != NULL) {
		game_world = child->GetGameWorld();
	}
}

int UIManager::GetYear() {
	return game_world->GetGameTime().GetYear().val;
}
int UIManager::GetMonth() {
	return game_world->GetGameTime().GetMonth().val;
}
int UIManager::GetDay() {
	return game_world->GetGameTime().GetDay().val;
}
int UIManager::GetHour() {
	return game_world->GetGameTime().GetHour().val;
}
int UIManager::GetMinute() {
	return game_world->GetGameTime().GetMinute().val;
}