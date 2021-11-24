#pragma once

class UIService {
private:
	GameWorldForUI* game_world;
public:
	UIService(GameWorldForUI* _game_world) : game_world(_game_world) {}
	GameTime GetGameTime() {
		return game_world->GetGameTime();
	}
	Array GetSerialized_event_log() {
		return game_world->GetEventLogRepository()->GetSerialized_event_log();
	}
};