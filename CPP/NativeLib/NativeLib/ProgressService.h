#pragma once
#include "EventGenerator.h"
#include "Common.h"
#include "RepeatitionRandomOcccurrence.h"

class ProgressService {
private:
	ObjectService* object_service;
	RandomRepository* random_repo;
	TimeRepository* time_repo;
	EventLogRepository* event_log_repo;
	RepeatitionRandomOccurrence guest_visit_event;

	int test_guest_num = 1;

	void CreateNewTimeEvent() {

	}

	void VisitNewGuest() {
		event_log_repo->AddLog(EventLog(
			"Guest Visit", "Visit Guest " + to_string(test_guest_num), time_repo->CaptureGameTime()
		));
		test_guest_num++;
		object_service->CreateNewGuest();
	}
public:
	ProgressService(ObjectService* _object_service, RandomRepository* _random_repo,
		TimeRepository* _time_repo, EventLogRepository* _event_log_repo)
	: object_service(_object_service), random_repo(_random_repo),
		time_repo(_time_repo), event_log_repo(_event_log_repo){
		guest_visit_event.setProbability(0.07f);
	}

	void Update(float delta) {
		time_repo->TimeGo(delta);
		if (time_repo->SignalByPassOneTIck()) {
			if (guest_visit_event.isOccurrence(random_repo->GetRandomSeedByNowTime(time_repo->GetOverallTime()))) {
				VisitNewGuest();
			}
		}
	}
};