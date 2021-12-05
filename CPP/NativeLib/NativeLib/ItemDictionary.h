#pragma once
#include "IDGenerator.h"
#include "Material.h"
#include "StatItem.h"

class ItemDictionary {
private:
	IDGenerator* id_maker;
	vector<string> key_list;

	unordered_map<int, Item*> id_item_list;
	unordered_map<string, Item*> name_item_list;
	static ItemDictionary* instance;
	~ItemDictionary() {
		delete instance;
	}

public:
	static ItemDictionary* GetInstance();
	
	ItemDictionary();
	ItemDictionary(const ItemDictionary& ref){}
	ItemDictionary& operator=(const ItemDictionary& ref){}

	void GenerateDictionary();
	Item* MakeItem(string type, vector<string> sub_line_list);
	unordered_map<string, int> ParameterParsing(vector<string> sub_line_list);

	int GetIDByName(string name);
	Item* GetItemByID(string name);
	Item* GetItemByName(string name);
};
