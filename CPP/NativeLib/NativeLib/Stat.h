#pragma once
#include "StatField.h"
#include <string>
#include <vector>

using namespace std;

class Stat {
private:
    vector<StatField> list;
    StatField *FindStatField(eStatFieldType name);
public:
    int GetStatFieldValue(eStatFieldType name);
    void SetStatFieldValue(eStatFieldType name, int value);
    void AddStatFieldValue(eStatFieldType name, int value);
    Stat();
};
