#pragma once
#include <unordered_map>

#include "IDService.h"
#include "DisplayStand.h"
#include "EquipItem.h"

class ItemDictionaryService {
private:
	IDService* id_maker;
	unordered_map<int, Item*> id_item_list;

	unordered_map<string, Item*> name_item_list;
public:
	ItemDictionaryService(IDService* id_service):id_maker(id_service){
		SetDictionary();
	}
	void SetDictionary();
	Item* MakeItem(string type, vector<string> sub_line_list);
	void StatParsing(EquipItem* item, vector<string> sub_line_list);

	int GetIDByName(string name);
	Item* GetItemByID(string name);
	Item* GetItemByName(string name);
};