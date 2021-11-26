#include "NameGenerator.h"
#include "NameList.cpp"
#include <algorithm>
#include <random>

NameGenerator::NameGenerator(){
    load_name_data2();
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
        family_name_queue.push(list[i]);
}

void NameGenerator::FillManNameQueue(vector<string> &list){
    ShuffleList(list);
    for (int i = 0; i < list.size(); i++)
        man_name_queue.push(CharacterName(list[i], eNameType::MAN));
}

void NameGenerator::FillWomanNameQueue(vector<string> &list){
    ShuffleList(list);
    for (int i = 0; i < list.size(); i++)
        woman_name_queue.push(CharacterName(list[i], eNameType::WOMAN));
}
string NameGenerator::PickFamilyName(){
    string value = family_name_queue.front();
    family_name_queue.pop();
    family_name_queue.push(value);
    return value;
}

CharacterName GetNameFromQueue(queue<CharacterName> &q){
    CharacterName value = q.front();
    q.pop();
    return value;
}

CharacterName NameGenerator::PickManName(){
    if(man_name_queue.empty())
        return dummy_name;
    return GetNameFromQueue(man_name_queue);
}

CharacterName NameGenerator::PickWomanName(){
    if(woman_name_queue.empty())
        return dummy_name;
    return GetNameFromQueue(woman_name_queue);
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
    if(fullName.GetName() == dummy_name)
        return;
    if (fullName.GetType() == eNameType::MAN)
        man_name_queue.push(fullName.GetName());
    else
        woman_name_queue.push(fullName.GetName());
}
