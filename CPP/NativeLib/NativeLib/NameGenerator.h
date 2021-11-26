#pragma once
#include <queue>
#include "CharacterName.h"

class NameGenerator{
private:
    queue<string> familyNameQueue;
    queue<CharacterName> manNameQueue;
    queue<CharacterName> womanNameQueue;

    string PickFamilyName();
    CharacterName PickManName();
    CharacterName PickWomanName();
    void FillFamilyNameQueue(vector<string> &list);
    void FillManNameQueue(vector<string> &list);
    void FillWomanNameQueue(vector<string> &list);
public:
    NameGenerator();

    CharacterName dummyName = CharacterName("dummy", eNameType::MAN);

    CharacterFullName MakeFullName(eNameType gender);
    void ReturnName(CharacterFullName fullName);
};
