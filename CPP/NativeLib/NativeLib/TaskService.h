#pragma once
#include "Task.h"

class TaskService {
private:
	TileRepository* tile_repo;
	PathFindService* path_finder;
	queue<Vector2>* CreatePath(Vector2 start_position, Vector2 target_position) {
		return path_finder->PathFinding(start_position, target_position);
	}
public:
	TaskService(TileRepository* _tile_repo, PathFindService* _path_finder)
		: tile_repo(_tile_repo), path_finder(_path_finder) {}

	Task* CreateSeekTask(Character* c, Vector2 seek_target) {
		queue<Vector2>* paths = CreatePath(c->GetPhysics()->GetPosition(), seek_target);
		return new SeekTask(paths);
	}
	Task* CreateLeaveVillageTask(Character* c) {
		Vector2 leave_point = CoordinatesToCenterVector(c->GetSchedule()->GetVillageDeparturePoint());
		queue<Vector2>* paths = CreatePath(c->GetPhysics()->GetPosition(), leave_point);
		return new LeaveVillageTask(paths);
	}
	float GetRandomPoint(float now_point, float bound_max) {
		float new_point;
		float rand_var = rand() % 20 - 10;
		new_point = now_point + rand_var;
		if (new_point < 0) {
			new_point = 0;
		}
		if (new_point > bound_max) {
			new_point = bound_max;
		}
		//printf("[TaskService]new point: %f, rand_var : %f, now point : %f\n", new_point, rand_var, now_point);
		return new_point;
	}
	Task* CreateWanderTask(Character* c) {
		float max_x = TILE_WIDTH * DEFAULT_TILE_NUMBER_X, max_y = TILE_HEIGHT * DEFAULT_TILE_NUMBER_Y;
		Coordinates now_coor = AbsolutePositionToCoordinates(c->GetPhysics()->GetPosition());
		Coordinates wander_coor = Coordinates(GetRandomPoint(now_coor.x, max_x),GetRandomPoint(now_coor.y, max_y));

		while (!path_finder->IsPassableTile(wander_coor)) {
			wander_coor = Coordinates(GetRandomPoint(now_coor.x, max_x), GetRandomPoint(now_coor.y, max_y));
		}

		Vector2 wander_point = CoordinatesToCenterVector(wander_coor);
		queue<Vector2>* paths = CreatePath(c->GetPhysics()->GetPosition(), wander_point);
		return new WanderTask(paths);
	}
};