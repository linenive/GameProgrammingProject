#pragma once
#include "Common.h"
#include "WorldObject.h"
// To-do: 다른 태스크는 나중에 만들기
class Task{
private:
	Vector2 target;

public:
	Task(Vector2 target) : target(target) {}
	~Task() {
	}
	void SetTarget(Vector2 new_target);
	Vector2 GetTarget() { return target; }
	void ExecuteTask(WorldObject* performer);
};