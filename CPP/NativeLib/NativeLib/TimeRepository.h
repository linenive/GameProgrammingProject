#pragma once
#include "GameTime.h"

class TimeRepository {
private:
	GameTime now_game_time;

public:
	TimeRepository() : now_game_time(GameTime()){}
	void CheckEvent();
	void LoadTime(const Year& year, const Month& month,
		const Day& day, const Time& time, const Minute& minute);
	GameTime GetGameTime() { return now_game_time; }
};