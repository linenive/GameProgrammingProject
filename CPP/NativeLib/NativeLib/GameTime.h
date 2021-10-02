#pragma once
#include "GameRule.h"
#include "DateSystem.h"
#include "TimeSystem.h"

class GameTime
{
private:
	Date game_date;
	Time game_time;
	void NewDayCheckAndPassDay();

public:
	GameTime() : game_date(Date(Year(1), Month(1), Day(1))), game_time(Time(Hour(0), Minute(0))){}
	GameTime(Date date, Time time) : game_date(date), game_time(time) {}
	void PassOneTick();
	Year GetYear() { return game_date.GetYear(); }
	Month GetMonth() { return game_date.GetMonth(); }
	Day GetDay() { return game_date.GetDay(); }
	Hour GetHour() { return game_time.getHour(); }
	Minute GetMinute() { return game_time.getMinute(); }
};

