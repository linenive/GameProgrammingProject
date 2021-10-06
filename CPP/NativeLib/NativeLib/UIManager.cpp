#include "UIManager.h"

void UIManager::_register_methods() {
	register_method("_init", &UIManager::_ready);
	register_method("_ready", &UIManager::_ready);
	register_method("_process", &UIManager::_process);
	register_method("_physics_process", &UIManager::_physics_process);
	register_method("get_time", &UIManager::get_time);
}

void UIManager::get_time()
{

}

void UIManager::_init() {

}

void UIManager::_ready() {
}

void UIManager::_process(float delta) {
}

void UIManager::_physics_process(float delta) {
}