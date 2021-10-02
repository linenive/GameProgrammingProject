#pragma once
#include "GameRule.h"

struct Year
{
	explicit Year() : val(1) {}
	explicit Year(int y) : val(y) {}
	int val;
};

struct Month
{
	explicit Month() : val(1) {}
	explicit Month(int m) : val(m) {}
	int val;
};

struct Day
{
	explicit Day() : val(1) {}
	explicit Day(int d) : val(d) {}
	int val;
};

class Date
{
private:
	Year year;
	Month month;
	Day day;
	void PassOneMonth();
	void PassOneYear();
	bool IsLastDay();
	bool IsLastMonth();
	bool IsLastYear();

public:
	Date(const Year& y, const Month& m, const Day& d)
		: year(y), month(m), day(d) {}
	void PassOneDay();
	Year GetYear() { return year; }
	Month GetMonth() { return month; }
	Day GetDay() { return day; }
};