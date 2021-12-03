#pragma once
#include "GameWorld.h"
#include "PathFindService.h"
#include "ObjectService.h"
#include "TaskService.h"
#include "StaticUnitService.h"
#include "UIService.h"
#include "ControlContextService.h"
#include "TileService.h"
#include "VillageService.h"
#include "ProgressService.h"
#include "AIService.h"
#include "ResidentService.h"
#include "SkillService.h"

class GameService{

private:
	GameWorld game_world;

public:
	PathFindService* path_find_service;
	ObjectService* object_service;
	TaskService* task_service;
	StaticUnitService* static_unit_service;
	UIService* ui_service;
	ControlContextService* control_context_service;
	TileService* tile_service;
	VillageService* village_service;
	ProgressService* progress_service;
	AIService* ai_service;
	ResidentService* resident_service;
	SkillService* skill_service;
	
	~GameService() {
		delete object_service;
		delete task_service;
		delete static_unit_service;
		delete ui_service;
		delete control_context_service;
		delete tile_service;
		delete village_service;
		delete progress_service;
		delete ai_service;
		delete resident_service;
		delete skill_service;
	}

	GameService() {
		// 생성 시 repository만 필요한 서비스들
		path_find_service = new PathFindService(&game_world.tile_repo);
		village_service = new VillageService(&game_world.village_repo);
		tile_service = new TileService(&game_world.tile_repo);
		static_unit_service = new StaticUnitService(
			&game_world.tile_repo, &game_world.structure_repo, &game_world.building_repo
		);
		ui_service = new UIService(
			&game_world.time_repo, &game_world.event_log_repo
		);
		skill_service = new SkillService(
			&game_world.skill_repo
		);

		// 생성 시 다른 서비스를 받는 서비스들
		object_service = new ObjectService(
			&game_world.object_repo,
			skill_service
		);
		task_service = new TaskService(
			&game_world.tile_repo, path_find_service, resident_service
		);
		control_context_service = new ControlContextService(
			&game_world.tile_repo, static_unit_service
		);
		progress_service = new ProgressService(
			object_service, &game_world.random_repo,
			&game_world.time_repo, &game_world.event_log_repo
		);
		ai_service = new AIService(
			object_service, task_service
		);
		resident_service = new ResidentService(
			object_service,
			&game_world.object_repo, &game_world.building_repo
		);
	};

};
