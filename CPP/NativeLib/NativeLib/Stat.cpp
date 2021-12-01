#include "Stat.h"

Stat::Stat() {
   
}

StatField* Stat::FindStatField(eStatFieldType name) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i].GetName() == name) {
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
