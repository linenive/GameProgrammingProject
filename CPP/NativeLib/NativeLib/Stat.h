#pragma once
#include "StatField.h"
#include <string>
#include <vector>

using namespace std;

class Stat {
private:
public:
    vector<StatField> list;

    StatField* FindStatField(eStatFieldType name);
    int GetStatFieldValue(eStatFieldType name);
    void SetStatFieldValue(eStatFieldType name, int value);
    void AddStatFieldValue(eStatFieldType name, int value);
    Stat();
    Stat(Stat* other_stat);
};
