#pragma once
#include "Task.h"
#include "ResidentService.h"
#include "UIService.h"
#include "WorkPriority.h"

class TaskService {
private:
	TileService* tile_service;
	PathFindService* path_finder;
	ResidentService* resident_service;
	queue<Vector2>* CreatePath(Vector2 start_position, Vector2 target_position) {
		return path_finder->PathFinding(start_position, target_position);
	}
public:
	TaskService(TileService* _tile_service, PathFindService* _path_finder,
		ResidentService* _resident_service)
		: tile_service(_tile_service), path_finder(_path_finder), resident_service(_resident_service) {}

	Task* CreateSeekTaskToHome(Resident* character) {
		Vector2 home_pos = resident_service->GetResidentHomePosition(character->GetId());
		return CreateSeekTask(character, home_pos);
	}
	Task* CreateSeekTaskToWorkSpace(Resident* character) {
		Vector2 home_pos = resident_service->GetResidentWorkSpacePosition(character->GetId());
		return CreateSeekTask(character, home_pos);
	}
	Task* CreateSeekTask(Character* c, Vector2 seek_target) {
		queue<Vector2>* paths = CreatePath(c->GetPhysics()->GetPosition(), seek_target);
		return new SeekTask(paths);
	}
	Task* CreateLeaveVillageTask(Guest* c) {
		Vector2 leave_point = CoordinatesToCenterVector(c->GetSchedule()->GetVillageDeparturePoint());
		queue<Vector2>* paths = CreatePath(c->GetPhysics()->GetPosition(), leave_point);
		return new LeaveVillageTask(paths);
	}
	void SetTaskPathTempFunc(ShoppingTask* task, Character* c, Vector2 seek_target) {
		task->SetPath(CreatePath(c->GetPhysics()->GetPosition(), seek_target));
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
		return new_point;
	}
	Task* CreateWanderTask(Character* c) {
		float max_x = TILE_WIDTH * DEFAULT_TILE_NUMBER_X, max_y = TILE_HEIGHT * DEFAULT_TILE_NUMBER_Y;
		Coordinates now_coord = AbsolutePositionToCoordinates(c->GetPhysics()->GetPosition());
		Coordinates wander_coord = Coordinates(GetRandomPoint(now_coord.x, max_x),GetRandomPoint(now_coord.y, max_y));

		while (!tile_service->IsPassableTile(wander_coord)) {
			wander_coord = Coordinates(GetRandomPoint(now_coord.x, max_x), GetRandomPoint(now_coord.y, max_y));
		}

		Vector2 wander_point = CoordinatesToCenterVector(wander_coord);
		queue<Vector2>* paths = CreatePath(c->GetPhysics()->GetPosition(), wander_point);
		return new WanderTask(paths);
	}
	Task* CreateWorkTask(eWorkType work_type, Inventory* target_inventory, int work_count) {
		return new WorkTask(work_type, target_inventory, work_count, 
			work_type == eWorkType::COLLECT_WOOD ? 50 : 300); //hardcoding... T.T
	}
	Task* CreateShoppingTask(Building* shop, int wish_item_code) {
		return new ShoppingTask(shop, wish_item_code);
	}
};