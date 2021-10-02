#include "TimeSystem.h"

void Time::PassOneMinute() {
	if (IsLastMinute()) {
		PassOneHour();
		minute.val = 0;
	}
	else {
		minute.val++;
	}
}

bool Time::IsDayOver()
{
	return hour.val == 0 && minute.val == 0;
}

void Time::PassOneHour() {
	if (IsLastHour()) {
		hour.val = 0;
	}
	else {
		hour.val++;
	}
}

bool Time::IsLastMinute() {
	return minute.val == MINUTE_PER_HOUR;
}

bool Time::IsLastHour() {
	return hour.val == HOUR_PER_DAY;
}
