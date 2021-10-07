#pragma once
#include "DateSystem.h"
#include "TimeSystem.h"

class GameTime
{
private:
	Date game_date;
	Time game_time;
	void NewDayCheckAndPassDay();

public:
	GameTime() : game_date(Date(
		Year(DEFAULT_START_YEAR),
		Month(DEFAULT_START_MONTH),
		Day(DEFAULT_START_DAY))),
		game_time(Time(Hour(DEFAULT_START_HOUR), Minute(DEFAULT_START_MINUTE))){}
	GameTime(Date date, Time time) : game_date(date), game_time(time) {}
	void PassOneTick();
	Year GetYear() { return game_date.GetYear(); }
	Month GetMonth() { return game_date.GetMonth(); }
	Day GetDay() { return game_date.GetDay(); }
	Hour GetHour() { return game_time.getHour(); }
	Minute GetMinute() { return game_time.getMinute(); }
};

