#include "UIManager.h"
#include "GodotScenePath.h"

void UIManager::_register_methods() {
	register_method("_init", &UIManager::_init);
	register_method("_ready", &UIManager::_ready);
	register_method("_process", &UIManager::_process);
	register_method("GetYear", &UIManager::GetYear);
	register_method("GetMonth", &UIManager::GetMonth);
	register_method("GetDay", &UIManager::GetDay);
	register_method("GetHour", &UIManager::GetHour);
	register_method("GetMinute", &UIManager::GetMinute);
	register_method("GetEventLogs", &UIManager::GetEventLogs);
	register_method("TestFunc", &UIManager::TestFunc);
}

void UIManager::_init(){
	
}

void UIManager::_ready() {
	LoadGameService();
}

void UIManager::_process(float delta) {
	
}

void UIManager::LoadGameService() {
	Node* node = get_node(NodePath(String(SCENEPATH_GAMEMANAGER.c_str())));
	ERR_FAIL_COND(node == nullptr);
	GameManager* child = node->cast_to<GameManager>(node);
	ERR_FAIL_COND(child == nullptr);
	ui_service = child->GetGameService()->ui_service;
}

int UIManager::GetYear() {
	return ui_service->GetGameTime().GetYear().val;
}
int UIManager::GetMonth() {
	return ui_service->GetGameTime().GetMonth().val;
}
int UIManager::GetDay() {
	return ui_service->GetGameTime().GetDay().val;
}
int UIManager::GetHour() {
	return ui_service->GetGameTime().GetHour().val;
}
int UIManager::GetMinute() {
	return ui_service->GetGameTime().GetMinute().val;
}