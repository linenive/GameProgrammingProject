#include "testProperty.h"

using namespace godot;

Skill::Skill(int skillLevel, godot::String skillName){
    level = skillLevel;
    name = skillName;
    test_data_a = 0;
    test_data_b = false;
}

void Skill::SetData(int a, bool b){
    test_data_a = a;
    test_data_b = b;
}