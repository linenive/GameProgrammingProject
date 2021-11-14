#pragma once
#include "EventGenerator.h"
#include "GameWorldForEvent.h"
#include "Common.h"
#include "RepeatitionRandomOcccurrence.h"

class ProgressManager {
private:
	GameWorldForEvent* game_world;
	TimeRepository* time_repo;
	RepeatitionRandomOccurrence guest_visit_event;

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
			guest_visit_event.checkOccurrence(game_world->GetRandomSeedByNowTime());
		}
	}
};