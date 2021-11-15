#pragma once
#include "Common.h"
#include "WorldObject.h"
#include <vector>

// To-do: 다른 태스크는 나중에 만들기
class Task{
private:
	Vector2 current_target;
	Vector2 task_target;

	vector<Vector2> path_list;
	int current_path_index;
	int current_path_list_length;
	bool current_moving;

public:
	Task(Vector2 target) : task_target(target) {}
	~Task() {
	}
	Vector2 GetTarget() { return task_target; }

	void ChangeTarget(vector<Vector2> path_list, Vector2 new_target); 
	bool CanChangeNextPos();
	void ExecuteTask(WorldObject* performer);
	bool ArriveCurrentTarget(Vector2 current_position);
};