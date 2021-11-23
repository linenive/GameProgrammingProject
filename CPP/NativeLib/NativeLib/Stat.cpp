#include "Stat.h"

Stat::Stat() {
    // Just Example
    // move speed
    list.push_back(StatField(BASE_MOVE_SPEED, 0));
    list.push_back(StatField(MOVE_SPEED_ON_HEAVY, 0));

    // carrige weight
    list.push_back(StatField(MAX_WEIGHT, 0));

    // job speed
    list.push_back(StatField(BASE_WORK_SPEED, 0));
    list.push_back(StatField(LOGGING_WORK_SPEED, 0));
    list.push_back(StatField(BLACKSMITH_WORK_SPEED, 0));

    // battle
    list.push_back(StatField(BASE_COMBAT_LEVEL, 0));
    list.push_back(StatField(COMBAT_LEVEL_AGAINST_UNDEAD, 0));

    // special ability, work like boolean
    list.push_back(StatField(CAN_WORK_UNTIL_MIDNIGHT, 0));
}

StatField* Stat::FindStatField(eStatFieldName name) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i].GetName() == name) {
            return &list[i];
        }
    }
}

int Stat::GetStatFieldValue(eStatFieldName name) {
    return FindStatField(name)->GetValue();
}
void Stat::SetStatFieldValue(eStatFieldName name, int value) {
    FindStatField(name)->SetValue(value);
}
void Stat::AddStatFieldValue(eStatFieldName name, int value) {
    FindStatField(name)->AddValue(value);
}
