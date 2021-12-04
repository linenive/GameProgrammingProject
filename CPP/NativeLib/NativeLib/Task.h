#pragma once
#include "Action.h"
#include <queue>

enum class eTaskType {
	NONE, SEEK, LEAVE_VILLAGE, WANDER
};

class Task{
protected:
	Action* current_action = nullptr;
	
public:
	~Task() {
		delete current_action;
		current_action = nullptr;
	}
	virtual void NextAction() = 0;
	bool HasAction() { return current_action != nullptr; }

	void Execute(Character* performer) {
		
		if (current_action->IsEndAction(performer)) {
			NextAction();
			if (!HasAction()) { return; }
		}
		current_action->ExecuteAction(performer);
	}

	virtual const eTaskType GetType() = 0;
};

class SeekTask : public Task {
protected:
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

	virtual void NextAction() {
		delete current_action;
		current_action = nullptr;
		
		if (!paths->empty()) {
			current_action = new MoveAction(paths->front());
			paths->pop();
		}
		else {
			// To-do: 이걸 빼면 에러가 나는 이유 찾기
			current_action = new PauseAction();
		}
	}
	// To-do: 수행 도중 갈 수 없게 된 경우 태스크 삭제하고 다시 새로운 Task로 시작됨
	
	virtual const eTaskType GetType() {
		return eTaskType::SEEK;
	}
};

class LeaveVillageTask : public SeekTask {
private:

public:
	~LeaveVillageTask () {
		delete paths;
	}
	LeaveVillageTask(queue<Vector2>* _paths) : SeekTask(_paths) {
		NextAction();
	}

	virtual void NextAction() {
		delete current_action;
		current_action = nullptr;

		if (!paths->empty()) {
			current_action = new MoveAction(paths->front());
			paths->pop();
		}
		else {
			current_action = new PauseAction();
		}
	}

	// To-do: 수행 도중 갈 수 없게 된 경우 태스크 삭제하고 다시 새로운 Task로 시작됨

	virtual const eTaskType GetType() {
		return eTaskType::LEAVE_VILLAGE;
	}
};

class WanderTask : public SeekTask {

public:
	~WanderTask() {
		delete paths;
	}
	WanderTask(queue<Vector2>* _paths) : SeekTask(_paths) {
		NextAction();
	}
	virtual const eTaskType GetType() {
		return eTaskType::WANDER;
	}
};