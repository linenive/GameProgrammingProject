#pragma once
#include "TimeRepository.h"
#include "TileRepository.h"
#include "ObjectRepository.h"
#include "VillageRepository.h"
#include "EventLogRepository.h"
#include "BuildingRepository.h"
#include "RandomRepository.h"
#include "SkillRepository.h"

class GameWorld {

public:
	TimeRepository time_repo;
	TileRepository tile_repo;
	ObjectRepository object_repo;
	VillageRepository village_repo;
	EventLogRepository event_log_repo;
	BuildingRepository building_repo;
	RandomRepository random_repo;
	SkillRepository skill_repo;
};
