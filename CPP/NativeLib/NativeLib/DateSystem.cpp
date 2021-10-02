#include "DateSystem.h"

void Date::PassOneDay() {
	if (IsLastDay()) {
		PassOneMonth();
		day.val = 1;
	}
	else {
		day.val++;
	}
}

void Date::PassOneMonth() {
	if (IsLastMonth()) {
		PassOneYear();
		month.val = 1;
	}
	else {
		month.val++;
	}
}

void Date::PassOneYear() {
	// 최대 연도에 도달했을 때 0년도로 돌아가게 하면,
	// 게임 내 역사적 이벤트가 다시 반복되어 이상하므로, 마지막 연도에서 멈추게 했음.
	if (IsLastYear()) return;
	year.val++;
}

bool Date::IsLastDay(){
	return day.val == DAYS_PER_MONTH;
}

bool Date::IsLastMonth(){
	return month.val == MONTH_PER_YEAR;
}

bool Date::IsLastYear(){
	return year.val == YEAR_MAXIMUM;
}
