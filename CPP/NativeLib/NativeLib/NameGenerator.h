#pragma once
#include <queue>
#include "CharacterName.h"

class NameGenerator{
private:
    queue<string> family_name_queue;
    queue<CharacterName> man_name_queue;
    queue<CharacterName> woman_name_queue;

    string PickFamilyName();
    CharacterName PickManName();
    CharacterName PickWomanName();
    void FillFamilyNameQueue(vector<string> &list);
    void FillManNameQueue(vector<string> &list);
    void FillWomanNameQueue(vector<string> &list);
public:
    NameGenerator();

    CharacterName dummy_name = CharacterName("dummy", eNameType::MAN);

    CharacterFullName MakeFullName(eNameType gender);
    void ReturnName(CharacterFullName fullName);
};
