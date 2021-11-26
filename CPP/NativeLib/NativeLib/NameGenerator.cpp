#include "NameGenerator.h"
#include "NameList.cpp"
#include <algorithm>
#include <random>

NameGenerator::NameGenerator(){
    //load_name_data_godot();
    FillFamilyNameQueue(family_name_list);
    FillManNameQueue(man_name_list);
    FillWomanNameQueue(woman_name_list);
}

void ShuffleList(vector<string> &list){
    std::random_device rd;
    std::shuffle(list.begin(), list.end(), default_random_engine(rd()));
}

void NameGenerator::FillFamilyNameQueue(vector<string> &list){
    ShuffleList(list);
    for (int i = 0; i < list.size(); i++)
        familyNameQueue.push(list[i]);
}

void NameGenerator::FillManNameQueue(vector<string> &list){
    ShuffleList(list);
    for (int i = 0; i < list.size(); i++)
        manNameQueue.push(CharacterName(list[i], eNameType::MAN));
}

void NameGenerator::FillWomanNameQueue(vector<string> &list){
    ShuffleList(list);
    for (int i = 0; i < list.size(); i++)
        womanNameQueue.push(CharacterName(list[i], eNameType::WOMAN));
}
string NameGenerator::PickFamilyName(){
    string value = familyNameQueue.front();
    familyNameQueue.pop();
    familyNameQueue.push(value);
    return value;
}

CharacterName GetNameFromQueue(queue<CharacterName> &q){
    CharacterName value = q.front();
    q.pop();
    return value;
}

CharacterName NameGenerator::PickManName(){
    if(manNameQueue.empty())
        return dummyName;
    return GetNameFromQueue(manNameQueue);
}

CharacterName NameGenerator::PickWomanName(){
    if(womanNameQueue.empty())
        return dummyName;
    return GetNameFromQueue(womanNameQueue);
}

CharacterFullName NameGenerator::MakeFullName(eNameType gender){
    if (gender == eNameType::MAN) {
        return CharacterFullName(PickFamilyName(), PickManName());
    }
    else {
        return CharacterFullName(PickFamilyName(), PickWomanName());
    }
}

void NameGenerator::ReturnName(CharacterFullName fullName){
    if(fullName.GetName() == dummyName)
        return;
    if (fullName.GetType() == eNameType::MAN)
        manNameQueue.push(fullName.GetName());
    else
        womanNameQueue.push(fullName.GetName());
}
