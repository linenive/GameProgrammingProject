#include "Stat.h"

Stat::Stat() {
    //밑에는 예시이며 삭제하거나 수정하거나 추가해도 됨.
    //이동 속도
    list.push_back(StatField(BASE_MOVE_SPEED, 0));
    list.push_back(StatField(MOVE_SPEED_ON_HEAVY, 0));

    //운반 할 수 있는 무게
    list.push_back(StatField(MAX_WEIGHT, 0));

    //작업 속도
    list.push_back(StatField(BASE_WORK_SPEED, 0));
    list.push_back(StatField(LOGGING_WORK_SPEED, 0));
    list.push_back(StatField(BLACKSMITH_WORK_SPEED, 0));

    //전투 관련
    list.push_back(StatField(BASE_COMBAT_LEVEL, 0));
    list.push_back(StatField(COMBAT_LEVEL_AGAINST_UNDEAD, 0));

    //특수 능력, bool 처럼 취급
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
