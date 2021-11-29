#pragma once
#include "GameTime.h"
#include "Timer.h"

class TimeRepository {
private:
	GameTime now_game_time;

public:
	TimeRepository() : now_game_time(GameTime()){}
	void CheckEvent();
	void LoadTime(const Year& year, const Month& month,
		const Day& day, const Time& time, const Minute& minute);
	GameTime GetGameTime() { return now_game_time; }
	GameTime CaptureGameTime() {
		return GameTime(
			Date(Year(now_game_time.GetYear().val), Month(now_game_time.GetMonth().val), Day(now_game_time.GetDay().val)),
			Time(Hour(now_game_time.GetHour().val), Minute(now_game_time.GetMinute().val))
		);
	}
	void PassOneTick() {
		now_game_time.PassOneTick();
	}
	unsigned int GetOverallTime() {
		return now_game_time.GetYear().val * MONTH_PER_YEAR * DAYS_PER_MONTH * HOUR_PER_DAY * MINUTE_PER_HOUR
			+ now_game_time.GetMonth().val * DAYS_PER_MONTH * HOUR_PER_DAY * MINUTE_PER_HOUR
			+ now_game_time.GetDay().val * HOUR_PER_DAY * MINUTE_PER_HOUR
			+ now_game_time.GetHour().val * MINUTE_PER_HOUR
			+ now_game_time.GetMinute().val;
	}
};