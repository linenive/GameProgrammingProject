#pragma once
#include <string>
#include "Common.h"
#include "GameRule.h"

class Village {
private:
	string name;
	int money = 0;

public:
	Village(string name) {
		this->name = name;
		money = 10000000;
	}
	string GetVillageName() { return name; }
	void SetVillageName(string name) {this->name = name;}

	int GetMoney() { return money; }
	void SetMoney(int money) { this->money = money; }
};