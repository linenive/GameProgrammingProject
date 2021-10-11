#pragma once
#include "Common.h"
#include "GameManager.h"
#include "GameRule.h"
#include "PopupUI.h"
#include <Node.hpp>
#include <list>

class UIManager : public Node {
	GODOT_CLASS(UIManager, Node);

private:
	GameWorldForUI* game_world;
	PopupUI* popups[MAXIMUM_UI_COUNT];
	list<PopupUI*> used_ui_list;

	void GetGameWorld();

public:
	static void _register_methods();
	void _init() {};
	void _ready();
	void _process(float delta);

	int GetYear();
	int GetMonth();
	int GetDay();
	int GetHour();
	int GetMinute();

	void ShowPopupUI();
	Vector2 GetTopUIPos();
	godot::String SetTitle(int type);
};