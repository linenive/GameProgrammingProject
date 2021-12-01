#include "Stat.h"

Stat::Stat() {
    for (int field_value : StatField::field_order) {
        list.push_back(StatField(static_cast<eStatFieldType>(field_value),0));
   }
}

Stat::Stat(Stat* other_stat) {
    for (auto field : other_stat->list) {
        list.push_back(field);
    }
}

StatField* Stat::FindStatField(eStatFieldType name) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i].GetType() == name) {
            return &list[i];
        }
    }
}

int Stat::GetStatFieldValue(eStatFieldType name) {
    return FindStatField(name)->GetValue();
}
void Stat::SetStatFieldValue(eStatFieldType name, int value) {
    FindStatField(name)->SetValue(value);
}
void Stat::AddStatFieldValue(eStatFieldType name, int value) {
    FindStatField(name)->AddValue(value);
}
