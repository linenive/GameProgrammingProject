#pragma once
#include "Common.h"
#include "WorldObject.h"
// To-do: �ٸ� �½�ũ�� ���߿� �����
class Task{
private:
	Vector2 target;

public:
	Task(Vector2 target) : target(target) {}
	~Task() {
	}
	void ExecuteTask(WorldObject* performer);
};