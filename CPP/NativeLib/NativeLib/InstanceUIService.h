#pragma once
#include "Common.h"
#include "InstanceUI.h"
#include "AIService.h"
#include <queue>
#include <unordered_map>
class InstanceUIService {
private:
	AIService* ai_service;

	unordered_map<int, InstanceUI*> current_instance_uis;
	bool HasInstanceUIByID(int id) {
		return current_instance_uis.find(id) != current_instance_uis.end();
	}
public:
	queue<int> new_instance_uis;
	queue<int> deleted_instance_uis;
	int test = 10;

	InstanceUIService(AIService* _ai_service) :ai_service (_ai_service){
	}
	void UpdateCurrentInstaneUIs() {
		vector<int> task_id_list = ai_service->GetTaskIDList();

		for (auto it : task_id_list) {
			if (current_instance_uis.find(it) == current_instance_uis.end()) {
				printf("add instance ui %d\n", it);
				new_instance_uis.push(it);
			}
		}

		for (auto it : current_instance_uis) {
			if (ai_service->HasTaskByID(it.first) == false) {
				printf("delete instance ui %d\n", it);
				deleted_instance_uis.push(it.first);
			}
		}
	}

	void AddInstanceUI(InstanceUI* new_ui) {
		current_instance_uis.insert(make_pair(new_ui->GetCharacterID(), new_ui));
	}

	void DeleteInstanceUI(InstanceUI* ui) {
		DeleteInstanceUI(ui->GetCharacterID());
	}
	void DeleteInstanceUI(int id) {
		if (HasInstanceUIByID(id))
			current_instance_uis.erase(id);
	}
	float GetInstanceValue(int id) {
		if (HasInstanceUIByID(id))
			current_instance_uis[id]->GetCurrentValue();
		else
			return -1;
	}
};