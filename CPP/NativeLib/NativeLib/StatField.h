#pragma once
#include <string>
#include <vector>

using namespace std;

enum eStatFieldName;

class StatField {
private:
    eStatFieldName name;
    int value;

public:
    StatField(eStatFieldName name, int value) : name(name), value(value) {};

    eStatFieldName GetName() { return name; }
    void SetValue(int value) { this->value = value; }
    void AddValue(int value) { this->value += value; }
    int GetValue() { return value; }
};

enum eStatFieldName {
    BASE_MOVE_SPEED,
    MOVE_SPEED_ON_HEAVY,
    MAX_WEIGHT,
    BASE_WORK_SPEED,
    LOGGING_WORK_SPEED,
    BLACKSMITH_WORK_SPEED,
    BASE_COMBAT_LEVEL,
    COMBAT_LEVEL_AGAINST_UNDEAD,
    CAN_WORK_UNTIL_MIDNIGHT
};