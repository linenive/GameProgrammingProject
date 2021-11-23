#pragma once

class UIService {
private:
	GameWorldForUI* game_world;
public:
	UIService(GameWorldForUI* _game_world) : game_world(_game_world) {}
	GameTime GetGameTime() {
		game_world->GetGameTime();
	}
	Array GetSerialized_event_log() {
		game_world->GetEventLogRepository()->GetSerialized_event_log();
	}
};