#pragma once
#include "TaskForMove.h"

class TaskForIdleMove : public TaskForMove {

protected:
	void ArriveTaskTarget() override;
	void CreateTimer(float wait_time);
public:
	TaskForIdleMove(TileRepository* tile, WorldObject* performer):TaskForMove(tile) {
		type = eTaskType::TASK_IDLE;

		current_position = performer->GetPhysics().GetPosition();
		SetIdleMove();
	}
	~TaskForIdleMove() {
	}
	//void ExecuteTask(WorldObject* performer) override;

	void SetIdleMove();
	Vector2 GetNewTarget();

	void Wait();
};