#pragma once
#include "StatField.h"
#include <string>
#include <vector>

using namespace std;

class Stat {
private:
    StatField *FindStatField(eStatFieldType name);
public:
    vector<StatField> list;

    int GetStatFieldValue(eStatFieldType name);
    void SetStatFieldValue(eStatFieldType name, int value);
    void AddStatFieldValue(eStatFieldType name, int value);
    Stat();
    Stat(Stat* other_stat);
};
