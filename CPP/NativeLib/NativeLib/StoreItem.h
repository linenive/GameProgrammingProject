#pragma once
#include "Item.h"

class StoreItem : public Item {

public:
	StoreItem(string name ):Item(name, "StoreItem"){}
};