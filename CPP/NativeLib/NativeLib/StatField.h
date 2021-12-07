#pragma once

#include "FileReader.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

enum class eStatFieldType;

class StatField {
private:
    eStatFieldType type;
    int value;

    // data from csv files
    static map<eStatFieldType, string> name_map;

public:
    static vector<int> field_order;

    StatField(eStatFieldType type, int value) : type(type), value(value) {};
    eStatFieldType GetType() { return type; }
    void SetValue(int value) { this->value = value; }
    void AddValue(int value) { this->value += value; }
    int GetValue() { return value; }
    static string NameOf(eStatFieldType name) {
        return name_map[name];
    }
    static void Init();
};

enum class eStatFieldType {
    BASE_MOVE_SPEED = 101,
    MOVE_SPEED_ON_HEAVY = 102,
    MAX_WEIGHT = 103,

    BASE_WORK_SPEED = 201,
    LOGGING_WORK_SPEED = 202,
    BLACKSMITH_WORK_SPEED = 203,
    MINING_SPEED = 204,
    ITEM_CREATE_SPEED = 205,
    SELL_ITEM_LEVEL = 206,

    BASE_COMBAT_LEVEL = 301,

    CAN_WORK_UNTIL_MIDNIGHT = 401
};
