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
	int GetYear() { return now_game_time.GetYear().val; }
	int GetMonth() { return now_game_time.GetMonth().val; }
	int GetDay() { return now_game_time.GetDay().val; }
	int GetHour() { return now_game_time.GetHour().val; }
	int GetMinute() { return now_game_time.GetMinute().val; }
};