#pragma once
#include "StatField.h"
#include <string>
#include <vector>

using namespace std;

class Stat {
private:
    vector<StatField> list;
    StatField *FindStatField(eStatFieldName name);
public:
    int GetStatFieldValue(eStatFieldName name);
    void SetStatFieldValue(eStatFieldName name, int value);
    void AddStatFieldValue(eStatFieldName name, int value);
    Stat();
};
