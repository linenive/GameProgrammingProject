#pragma once
#include "GameTime.h"
#include "Timer.h"

class TimeRepository {
private:
	GameTime now_game_time;
	Timer time_update_interval;

public:
	TimeRepository() : now_game_time(GameTime()),
		time_update_interval(Timer(UPDATE_INTERVAL_TIME)){}
	void CheckEvent();
	void LoadTime(const Year& year, const Month& month,
		const Day& day, const Time& time, const Minute& minute);
	GameTime GetGameTime() { return now_game_time; }
	void TimeGo(float delta);
	bool SignalByPassOneTIck() {
		return time_update_interval.isTimeZero();
	}
};