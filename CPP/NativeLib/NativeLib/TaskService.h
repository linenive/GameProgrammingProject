#pragma once
#include "PathFinder.h"
#include "Task.h"

class TaskService {
private:
	PathFinder path_finder;
	queue<Vector2>* CreatePath(Vector2 start_position, Vector2 target_position) {
		return path_finder.PathFinding(start_position, target_position);
	}
public:
	TaskService(GameWorldForTaskService* game_service) : path_finder(PathFinder(game_service->GetTileMap())) {}

	Task* CreateSeekTask(Character* c, Vector2 seek_target) {
		queue<Vector2>* paths = CreatePath(c->GetPhysics()->GetPosition(), seek_target);
		return new SeekTask(paths);
	}
};