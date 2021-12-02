#pragma once
#include <unordered_map>

#include "IDService.h"
#include "DisplayStand.h"
#include "OccupiedFurniture.h"

class ItemDictionaryService {
private:
	IDService* id_maker;
	unordered_map<int, Item*> id_item_list;

	unordered_map<string, Item*> name_item_list;
public:
	ItemDictionaryService(IDService* id_service):id_maker(id_service){
		SetDictionary();
	}
	void AddDictionary(string name, string type);
	void AddDictionaryFurniture(string name, string type, int grade);
	void AddDictionaryDisplayStand(string name, string type, int grade, int slot_max_count);
	void SetDictionary();

	int GetIDByName(string name);
	Item* GetItemByID(string name);
	Item* GetItemByName(string name);
};