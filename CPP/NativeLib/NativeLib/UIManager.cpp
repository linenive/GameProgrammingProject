#include "UIManager.h"
#include "ScenePath.h"
#include <string>

void UIManager::_register_methods() {
	register_method("_init", &UIManager::_init);
	register_method("_ready", &UIManager::_ready);
	register_method("_process", &UIManager::_process);
	register_method("GetYear", &UIManager::GetYear);
	register_method("GetMonth", &UIManager::GetMonth);
	register_method("GetDay", &UIManager::GetDay);
	register_method("GetHour", &UIManager::GetHour);
	register_method("GetMinute", &UIManager::GetMinute);

	register_method("ShowPopupUI", &UIManager::ShowPopupUI);
}

void UIManager::_ready() {
	Array children_node = get_node("/root/Main/UIManager/Popups")->get_children();

	for (int i = 0; i < MAXIMUM_UI_COUNT; i++)
	{
		PopupUI* ui = cast_to<PopupUI>(children_node[i]);
		popups[i] = ui;
		Godot::print(ui->get_name());
	}

	Godot::print("done!");
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

void UIManager::_process(float delta) {
	GetGameWorld();
}

int UIManager::GetYear() {
	return game_world->getGameTime().GetYear().val;
}
int UIManager::GetMonth() {
	return game_world->getGameTime().GetMonth().val;
}
int UIManager::GetDay() {
	return game_world->getGameTime().GetDay().val;
}
int UIManager::GetHour() {
	return game_world->getGameTime().GetHour().val;
}
int UIManager::GetMinute() {
	return game_world->getGameTime().GetMinute().val;
}

void UIManager::ShowPopupUI() {
	if (used_ui_list.size() == MAXIMUM_UI_COUNT) {
		PopupUI* top_ui = used_ui_list.front();
		top_ui->set_visible(false);
		used_ui_list.pop_front();
	}

	for (int i = 0; i < MAXIMUM_UI_COUNT; i++)
	{
		if (popups[i]->is_visible() == false)
		{
			used_ui_list.push_back(popups[i]);
			popups[i]->set_title(SetTitle(1) + popups[i]->get_name());
			popups[i]->set_position(GetTopUIPos());
			popups[i]->Pop();
			break;
		}
	}
}

Vector2 UIManager::GetTopUIPos() {
	WindowDialog* top_ui = cast_to<WindowDialog>(get_node("/root/Main/UIManager/Popups")->get_child(0));
	Vector2 pos = top_ui->get_position();
	pos += Vector2(20, 20);

	return pos;
}

godot::String UIManager::SetTitle(int type) {

	switch (type)
	{
	case 1:
		return "Character Info";
	case 2:
		return "아이템 정보";
	default:
		return "Popup_UI";
	}

}
