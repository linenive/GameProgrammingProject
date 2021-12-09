#pragma once
#include "Common.h"
#include "InstanceUIService.h"
#include <Node.hpp>
#include "GameManager.h"
#include "GodotScenePath.h"


class InstanceUIManager : public Node {
	GODOT_CLASS(InstanceUIManager, Node);

private:
	InstanceUIService* instance_ui_service;

	void EmitNewUI(int new_id) {
		printf("emit new ui %d\n", new_id);
		emit_signal(String("create_instance_ui"), new_id);
	}
	void EmitDeleteUI(int new_id) {
		printf("emit delete ui %d\n", new_id);
		emit_signal(String("delete_instance_ui"), new_id);
	}
	void FetchQueueAndSignal() {
		queue<int>* new_uis = &(instance_ui_service->new_instance_uis);
		queue<int>* delete_uis = &(instance_ui_service->deleted_instance_uis);

		while (!new_uis->empty()) {
			int new_ui = new_uis->front();
			new_uis->pop();
			EmitNewUI(new_ui);
		}
		while (!delete_uis->empty()) {
			int deleted_ui = delete_uis->front();
			delete_uis->pop();
			EmitDeleteUI(deleted_ui);
		}
	}
public:
	static void _register_methods() {
		register_method("_init", &InstanceUIManager::_init);
		register_method("_ready", &InstanceUIManager::_ready);
		register_method("_progress", &InstanceUIManager::_progress);
		register_method("GetInstanceValueByID", &InstanceUIManager::GetInstanceValueByID);

		register_signal<InstanceUIManager>(String("create_instance_ui"), "ID", GODOT_VARIANT_TYPE_INT,"Max", GODOT_VARIANT_TYPE_REAL);
		register_signal<InstanceUIManager>(String("delete_instance_ui"), "ID", GODOT_VARIANT_TYPE_INT, "Max", GODOT_VARIANT_TYPE_REAL);
	}

	void _init() {}
	void _ready() {
		Node* node = get_node(NodePath(SCENEPATH_GAMEMANAGER.c_str()));
		ERR_FAIL_COND(node == nullptr);
		GameManager* child = node->cast_to<GameManager>(node);
		ERR_FAIL_COND(child == nullptr);
		instance_ui_service = child->GetGameService()->instance_ui_service;

		printf("now %d", instance_ui_service->test);
	}
	void _progress(float delta) {
		instance_ui_service->UpdateCurrentInstaneUIs();
		FetchQueueAndSignal();
	}
	float GetInstanceValueByID(int id) {
		return instance_ui_service->GetInstanceValue(id);
	}
};