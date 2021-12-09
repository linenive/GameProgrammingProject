#pragma once

class UIService {
private:
	TimeRepository* time_repo;
	EventLogRepository* event_log_repo;
public:
	queue<int> ui_update_needed_character_ids;
	queue<int> ui_update_needed_structure_ids;
	queue<int> ui_update_needed_building_ids;

	queue<pair<int, Vector2>> money_alert_effects;

	UIService(TimeRepository* _time_repo, EventLogRepository* _event_log_repo)
		: time_repo(_time_repo), event_log_repo(_event_log_repo) {}
	GameTime GetGameTime() {
		return time_repo->GetGameTime();
	}
	Array GetSerializedEventLogs() {
		return event_log_repo->GetSerializedEventLogs();
	}
};