#pragma once
#include "Common.h"
#include "GameManager.h"
#include <Node.hpp>
#include <Array.hpp>

class UIManager : public Node {
	GODOT_CLASS(UIManager, Node);

private:
	UIService* ui_service;
	void LoadGameService();

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _process(float delta);

	Transform2D TestFunc() {
		return Transform2D(real_t(.0), Vector2(real_t(500.0), real_t(500.0)));
	}
	int GetYear();
	int GetMonth();
	int GetDay();
	int GetHour();
	int GetMinute();

	Array GetEventLogs() {
		return ui_service->GetSerializedEventLogs();
	}
};