#pragma once
#include "Item.h"

class BuildingItem : public Item {

public: 
	~BuildingItem() {
	}
	BuildingItem(string name): Item(name, "BuildingItem"){
	}

};
class FurnitureItem : public BuildingItem {

private:
	int grade = 0;

public: 
	~FurnitureItem() {
	}
	FurnitureItem(string name, int level) : BuildingItem(name), grade(grade) {
	}
};
