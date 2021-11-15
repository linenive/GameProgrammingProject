#pragma once
#include "Common.h"
#include "WorldObject.h"
#include <vector>

// To-do: 다른 태스크는 나중에 만들기
class Task{
private:
	Vector2 target;
	vector<Vector2> path_list;

public:
	Task(Vector2 target) : target(target) {}
	~Task() {
	}
	void ChangeTarget(Vector2 new_target);// vector<Vector2> path_list);
	Vector2 GetTarget() { return target; }
	void ExecuteTask(WorldObject* performer);
};