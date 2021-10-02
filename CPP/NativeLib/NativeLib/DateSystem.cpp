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
	// �ִ� ������ �������� �� 0�⵵�� ���ư��� �ϸ�,
	// ���� �� ������ �̺�Ʈ�� �ٽ� �ݺ��Ǿ� �̻��ϹǷ�, ������ �������� ���߰� ����.
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
