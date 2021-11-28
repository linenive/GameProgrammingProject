#pragma once
#include "Item.h"


class BuildItem : public Item {

public: 
	~BuildItem() {
	}
	BuildItem(string name, string type): Item(name, type){
	}

};
class FurnitureItem : public BuildItem {

protected:
	int grade = 0;

public: 
	~FurnitureItem() {
	}
	FurnitureItem(string name, string type, int grade) : BuildItem(name,type), grade(grade) {
	}
};

