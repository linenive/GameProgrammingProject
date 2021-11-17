#pragma once
#include "Task.h"
#include "PathFinder.h"
#include <vector>

class TaskForMove : public Task {

private:
	int current_path_index;
	int current_path_list_length;

protected:
	PathFinder path_finder = PathFinder();
	vector<Vector2> path_list;

	Vector2 current_position;
	Vector2 current_target;
	Vector2 task_target;

	bool current_moving;

	virtual void ArriveTaskTarget();

public:
	TaskForMove(TileRepository* tile) { 
		type = eTaskType::TASK_MOVE;
		path_finder.SetTileRepository(tile); 
	}
	~TaskForMove() {
	}
	Vector2 GetTarget() { return task_target; }
	Physics UpdatePosition(Physics performer_physics);

	void ChangeTarget(Vector2 new_start, Vector2 new_target);
	void SetPathList(Vector2 new_start, Vector2 new_target);
	bool CanChangeNextPos();

	void ExecuteTask(WorldObject* performer) override;
	bool CheckArriveCurrentTarget(Vector2 current_position);

};