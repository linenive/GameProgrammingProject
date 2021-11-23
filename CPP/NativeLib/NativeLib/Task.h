#pragma once
#include "Action.h"
#include <queue>

enum class eTaskType {
	NONE, SEEK
};

class Task{
protected:
	Action* current_action;
	
public:
	const eTaskType type = eTaskType::NONE;
	Task():current_action(nullptr){}
	~Task() {
		delete current_action;
	}
	virtual void NextAction() = 0;
	bool IsEnd() { return current_action == nullptr; }
	void Execute(WorldObject* performer) {
		if (current_action->IsEndAction(performer)) {
			NextAction();
		}
		current_action->ExecuteAction(performer);
	}
};

class SeekTask : public Task {
private:
	queue<Vector2>* paths;

	Vector2 GetFirstPath() {
		return paths->front();
	}

public:
	~SeekTask() {
		delete paths;
	}
	SeekTask(queue<Vector2>* _paths): paths(_paths){
		NextAction();
	}
	const eTaskType type = eTaskType::SEEK;

	bool IsEmptyPath() {
		return paths->size() == 0;
	}

	virtual void NextAction() {
		delete current_action;
		current_action = nullptr;

		if (!paths->empty()) {
			current_action = new MoveAction(paths->front());
			paths->pop();
		}
	}

	// To-do: 수행 도중 갈 수 없게 된 경우 태스크 삭제하고 다시 새로운 Task로 시작됨
	
};

class WanderTask : public Task {

};