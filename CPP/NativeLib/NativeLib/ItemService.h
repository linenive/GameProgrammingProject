#pragma once
#include "ItemDictionaryService.h"

class ItemService {
private:
	ItemDictionaryService* item_dictionary;
public:
	~ItemService(){
		delete item_dictionary;
	}
	ItemService(ItemDictionaryService* _item_dictionary):item_dictionary(_item_dictionary) {
	}
	Item* GetItemByName(string name) {
		return item_dictionary->GetItemByName(name);
	}
	FurnitureItem* GetFurnitureItemByName(string name) {
		FurnitureItem* new_furniture_item = (FurnitureItem *)item_dictionary->GetItemByName(name);
		return new_furniture_item;
	}
};