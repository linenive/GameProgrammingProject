#pragma once
#include "EventGenerator.h"
#include "GameWorldForEvent.h"
#include "Common.h"
#include "RepeatitionRandomOcccurrence.h"

class ProgressManager {
private:
	GameWorldForEvent* game_world;
	TimeRepository* time_repo;
	ObjectRepository* object_repo;
	RepeatitionRandomOccurrence guest_visit_event;

	int test_guest_num = 1;

	void CreateNewTimeEvent() {

	}
public:
	ProgressManager() {
		guest_visit_event.setProbability(0.1f);
	}
	void SetGameWorld(GameWorldForEvent* world) {
		game_world = world;
		time_repo = world->GetTimeRepository();
		object_repo = world->GetObjectRepository();
	}
	void Update(float delta) {
		time_repo->TimeGo(delta);
		if (time_repo->SignalByPassOneTIck()) {
			if (guest_visit_event.isOccurrence(game_world->GetRandomSeedByNowTime())) {
				// printf("[ProgressManager]guest visit\n");
				game_world->AddEventLog(EventLog("Guest Visit", "Visit Guest " + to_string(test_guest_num), time_repo->CaptureGameTime()));
				test_guest_num++;
				object_repo->CreateNewGuest();
			}
		}
	}
};