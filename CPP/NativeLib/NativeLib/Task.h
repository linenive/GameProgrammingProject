#pragma once
#include "Action.h"
#include "WorkPriority.h"
#include <queue>

enum class eTaskType {
	NONE, SEEK, LEAVE_VILLAGE, WANDER, WORK, SHOPPING,
};

class Task{
protected:
	Action* current_action = nullptr;
	bool is_task_done = false;
	
public:
	~Task() {
		delete current_action;
		current_action = nullptr;
	}
	
	virtual void NextAction() = 0;
	bool HasAction() { return current_action != nullptr; }
	bool IsTaskDone() { return is_task_done; }

	void Execute(Character* performer) {
		if (current_action->IsEndAction(performer)) {
			NextAction();
			if (!HasAction()) { 
				is_task_done = true;
				return; 
			}
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
			is_task_done = true;
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
			is_task_done = true;
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

class WorkTask : public Task {
private:
	eWorkType work_type;
	unsigned int left_action;
	Inventory* target_inventory;
	unsigned int action_time;
public:
	WorkTask(eWorkType type, Inventory* target_inventory, unsigned int action_num, unsigned int action_time)
		: work_type(type), target_inventory(target_inventory), 
		left_action(action_num), action_time(action_time) {
		current_action = new WorkAction(type, target_inventory, action_time);
	}

	virtual void NextAction() {
		left_action--;
		if (left_action > 0) {
			current_action = new WorkAction(work_type, target_inventory, action_time);
		}
		else {
			current_action = nullptr;
		}
	}

	virtual const eTaskType GetType() {
		return eTaskType::WORK;
	}
};

class ShoppingTask : public Task {
private:
	list<int> structure_list;
public:
	Building* shop;
	list<int>::iterator structure_iterator;
	int wish_item_code;
	ShoppingTask(Building* _shop, int _wish_item_code)
		: shop(_shop), wish_item_code(_wish_item_code) {
		structure_list = shop->inside_structures_list;
		structure_iterator = structure_list.begin();
		current_action = new PauseAction();
	}
	virtual void NextAction() {

	}

	virtual const eTaskType GetType() {
		return eTaskType::SHOPPING;
	}

	bool IsShoppingEnd() {
		return structure_iterator == structure_list.end();
	}

	void Done() {
		is_task_done = true;
	}

	void GoToNextStructure(Vector2 position) {
		current_action = new MoveAction(position);
	}
};