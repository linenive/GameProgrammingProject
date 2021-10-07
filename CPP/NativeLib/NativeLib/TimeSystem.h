#pragma once
#include "GameRule.h"

struct Hour{
	explicit Hour(int h) : val(h) {}
	int val;
};

struct Minute{
	explicit Minute(int m) : val(m) {}
	int val;
};

class Time{
private:
	Hour hour;
	Minute minute;
	void PassOneHour();
	bool IsLastMinute();
	bool IsLastHour();

public:
	Time(const Hour& h, const Minute& m) : hour(h), minute(m) {}
	void PassOneMinute();
	bool IsDayOver();
	Hour getHour() { return hour; }
	Minute getMinute() { return minute; }
};
