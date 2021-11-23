#pragma once
#include "GameWorld.h"
#include "ObjectService.h"
#include "TaskService.h"
#include "StaticUnitService.h"
#include "ProgressService.h"
#include "UIService.h"

#include "ControlState.h"


const unsigned int big_prime_number = 154813283;

class GameService{

private:
	GameWorld game_world;

public:
	ObjectService* object_service;
	TaskService* task_service;
	StaticUnitService* static_unit_service;
	ProgressService* progress_service;
	UIService* ui_service;

	ControlContext* control_context;
	
	~GameService() {
		delete object_service;
		delete task_service;
		delete static_unit_service;
		delete progress_service;
		delete ui_service;

		delete control_context;
	}
	GameService(){
		object_service = new ObjectService((GameWorldForObjectService*)&game_world);
		task_service = new TaskService((GameWorldForTaskService*)&game_world);
		static_unit_service = new StaticUnitService();
		progress_service = new ProgressService((GameWorldForProgressService*)&game_world);
		ui_service = new UIService((GameWorldForUI*)&game_world);
		control_context = new ControlContext((GameWorldForInput*)&game_world, static_unit_service);
	};

};
