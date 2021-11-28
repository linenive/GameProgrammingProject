#pragma once

#include "Building.h"

class House : public Building {
public:
    House(int _id, string _name, Rect2 _ocupation_area, int _character_slot_num)
        : Building(_id, _name,  _ocupation_area,_character_slot_num) {}
};
