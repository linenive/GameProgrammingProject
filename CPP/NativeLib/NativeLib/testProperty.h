#pragma once
#include "Common.h"

namespace godot{

class Skill
{
private:
    int level;
    godot::String name;
    int test_data_a;
    bool test_data_b;
public:
    Skill(int level, godot::String name);

    void SetData(int a, bool b);
    int GetLevel() { return level; };
    godot::String GetName(){return name;}
    int GetDataA(){return test_data_a;}
    bool GetDataB(){return test_data_b;}
};

}

