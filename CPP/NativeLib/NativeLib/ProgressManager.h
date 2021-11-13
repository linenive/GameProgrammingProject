#pragma once
#include "EventGenerator.h"
#include "GameWorldForEvent.h"
#include "Common.h"

class ProgressManager {
private:
	GameWorldForEvent* game_world;
	TimeRepository* time_repo;

	void createNewTimeEvent() {

	}
public:
	void SetGameWorld(GameWorldForEvent* world) {
		game_world = world;
		time_repo = world->GetTimeRepository();
	}
	void Update(float delta) {
		time_repo->TimeGo(delta);
		if (time_repo->SignalByPassOneTIck()) {
			
		}
	}
};