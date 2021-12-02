#include "BlockTypeProperty.h"

bool BlockTypeProperty::is_initialized;
int BlockTypeProperty::level[10];
string BlockTypeProperty::name[10];
float BlockTypeProperty::pass_speed[10];

int BlockTypeProperty::LevelOf(eBlockType type) {
    if (!is_initialized) {
        Init();
    }
    //To-do: check "Is value is in array"
    return BlockTypeProperty::level[static_cast<int>(type)];
}

string BlockTypeProperty::NameOf(eBlockType type) {
    if (!is_initialized) {
        Init();
    }
    return BlockTypeProperty::name[static_cast<int>(type)];
}

float BlockTypeProperty::PassSpeedOf(eBlockType type) {
    if (!is_initialized) {
        Init();
    }
    return BlockTypeProperty::pass_speed[static_cast<int>(type)];
}