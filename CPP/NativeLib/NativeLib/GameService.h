#pragma once
#include "GameWorld.h"
#include "PathFindService.h"
#include "ObjectService.h"
#include "TaskService.h"
#include "StaticUnitService.h"
#include "ProgressService.h"
#include "UIService.h"
#include "ControlContextService.h"

class GameService{

private:
	GameWorld game_world;

public:
	PathFindService* path_find_service;
	ObjectService* object_service;
	TaskService* task_service;
	StaticUnitService* static_unit_service;
	ProgressService* progress_service;
	UIService* ui_service;

	ControlContextService* control_context_service;
	
	~GameService() {
		delete object_service;
		delete task_service;
		delete static_unit_service;
		delete progress_service;
		delete ui_service;

		delete control_context_service;
	}
	GameService() {
		path_find_service = new PathFindService(&game_world.tile_repo);
		object_service = new ObjectService(&game_world.object_repo);
		task_service = new TaskService(
			&game_world.tile_repo, path_find_service
		);
		static_unit_service = new StaticUnitService(
			&game_world.tile_repo, &game_world.building_repo
		);
		progress_service = new ProgressService(
			object_service, &game_world.time_repo
		);
		ui_service = new UIService(
			&game_world.time_repo, &game_world.event_log_repo
		);
		control_context_service = new ControlContextService(
			&game_world.tile_repo, static_unit_service
		);
	};

};
