#pragma once
#include "StatField.h"
#include <string>
#include <vector>

using namespace std;

//스킬과 스탯은 밀접한 연관이 있음.
//스킬은 스탯을 조정하는 방향으로 적용됨.
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