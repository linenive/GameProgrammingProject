#pragma once
#include "Item.h"
class SaleItem : public Item {
private:
	int price;
public:
	SaleItem(string _name, string _type, int _price):Item(_name, _type), price(_price){
	}
	int GetPrice() { return price; }
};