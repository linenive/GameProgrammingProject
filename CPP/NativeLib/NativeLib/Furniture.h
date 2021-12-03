#pragma once
#include "Item.h"

class FurnitureItem : public Item {

protected:
	int grade = 0;
public: 
	FurnitureItem(string _name, string _type, int _grade) 
		: Item(_name,_type), grade(_grade) { }
};

