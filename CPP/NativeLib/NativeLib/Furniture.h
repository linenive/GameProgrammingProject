#pragma once
#include "Item.h"

class BuildItem : public Item {
public: 
	BuildItem(string _name, string _type): Item(_name, _type) { }
};
class FurnitureItem : public BuildItem {

protected:
	int grade = 0;
public: 
	FurnitureItem(string _name, string _type, int _grade) 
		: BuildItem(_name,_type), grade(_grade) { }
};

