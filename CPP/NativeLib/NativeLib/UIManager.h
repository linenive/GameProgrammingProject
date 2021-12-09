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

	void FetchQueueAndSignal() {
		queue<int>* ui_update_needed_character_ids = &(ui_service->ui_update_needed_character_ids);
		queue<int>* ui_update_needed_structure_ids = &(ui_service->ui_update_needed_structure_ids);
		queue<int>* ui_update_needed_building_ids = &(ui_service->ui_update_needed_building_ids);
		queue<pair<int, Vector2>>* money_alert_effects = &(ui_service->money_alert_effects);
	
		while (!ui_update_needed_character_ids->empty()) {
			int update_needed_character_id = ui_update_needed_character_ids->front();
			ui_update_needed_character_ids->pop();
			EmitCharacterInfoUpdateNeeded(update_needed_character_id);
		}

		while (!ui_update_needed_structure_ids->empty()) {
			int update_needed_structure_id = ui_update_needed_structure_ids->front();
			ui_update_needed_structure_ids->pop();
			EmitStructureInfoUpdateNeeded(update_needed_structure_id);
		}

		while (!ui_update_needed_building_ids->empty()) {
			int update_needed_building_id = ui_update_needed_building_ids->front();
			ui_update_needed_building_ids->pop();
			EmitBuildingInfoUpdateNeeded(update_needed_building_id);
		}

		while (!money_alert_effects->empty()) {
			pair<int, Vector2> data = money_alert_effects->front();
			money_alert_effects->pop();
			EmitMoneyAlertEffect(data.first, data.second);
		}
	}

	void EmitCharacterInfoUpdateNeeded(int character_id) {
		emit_signal(String("character_info_update_needed"), character_id);
	}

	void EmitStructureInfoUpdateNeeded(int structure_id) {
		emit_signal(String("structure_info_update_needed"), structure_id);
	}

	void EmitBuildingInfoUpdateNeeded(int building_id) {
		emit_signal(String("building_info_update_needed"), building_id);
	}

	void EmitMoneyAlertEffect(int money_variation, Vector2 effect_position) {
		emit_signal(String("money_alert_effect"), money_variation, effect_position);
	}
};