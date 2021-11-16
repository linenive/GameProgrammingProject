#pragma once

#include "StaticUnit.h"
#include "Character.h"
#include <vector>

using namespace std;

class Building : public StaticUnit {
public:
    Building(int _id, string _name, Rect2 _ocupation_area, int _character_slot_num)
        : StaticUnit(_id, _name, _ocupation_area), character_slot_num(_character_slot_num) {
    }
    //void AssignCharacter();

    int character_slot_num;
    vector<Character> character_slot;
};