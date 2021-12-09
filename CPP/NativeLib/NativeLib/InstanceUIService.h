#pragma once
#include "Common.h"
#include "InstanceUI.h"
#include "AIService.h"
#include <queue>
#include <unordered_map>
class InstanceUIService {
private:
	AIService* ai_service;

	vector<int> current_instance_uis;
	bool HasTaskByID(int id) {
		return find(current_instance_uis.begin(), current_instance_uis.end(), id) != current_instance_uis.end();
	}	
public:
	queue<pair<int,float>> new_instance_uis;
	queue<int> deleted_instance_uis;
	int test = 10;

	InstanceUIService(AIService* _ai_service) :ai_service (_ai_service){
	}
	void UpdateCurrentInstaneUIs() {
		vector<int> task_id_list = ai_service->GetTaskIDList();

		for (auto it : task_id_list) {
			if (HasTaskByID(it)==false) {
				Task* new_task = ai_service->GetTask(it);
				if (new_task->GetType() == eTaskType::WORK &&
					new_task->IsTaskDone()==false) {
					WorkTask* task = (WorkTask*)(ai_service->GetTask(it));
					new_instance_uis.push(make_pair(it, task->GetLeftTime()));
				}
			}
		}

		for (auto it : current_instance_uis) {
			Task* new_task = ai_service->GetTask(it);
			if (new_task == nullptr || new_task->IsTaskDone()) {
				deleted_instance_uis.push(it);
			}
		}
	}
	void AddInstanceUI(int id) {
		current_instance_uis.push_back(id);
	}
	void DeleteInstanceUI(int id) {
		auto it = find(current_instance_uis.begin(), current_instance_uis.end(), id);
		if (it != current_instance_uis.end()){
			current_instance_uis.erase(it);
		}
	}
	float GetInstanceValue(int id) {
		if (HasTaskByID(id)){
			if (ai_service->GetTask(id)->GetType() == eTaskType::WORK) {
				WorkTask* task = (WorkTask*)(ai_service->GetTask(id));
				return task->GetLeftTime();
			}
		}
		else
			return -1;
	}
};