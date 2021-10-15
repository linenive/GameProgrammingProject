#pragma once
#include "Skill.h"
#include <string>
#include <vector>
#include <iostream>

typedef eStatFieldName SFN;
class SkillRepository {
private:
    void Add(string name, SFN f1, int v1);
    void Add(string name, SFN f1, int v1, SFN f2, int v2);
    void Add(string name, SFN f1, int v1, SFN f2, int v2, SFN f3, int v3);
    void Add(string name, SFN f1, int v1, SFN f2, int v2, SFN f3, int v3, SFN f4, int v4);
    void Add(string name, SFN f1, int v1, SFN f2, int v2, SFN f3, int v3, SFN f4, int v4, SFN f5, int v5);
    void Add(string name, SFN f1, int v1, SFN f2, int v2, SFN f3, int v3, SFN f4, int v4, SFN f5, int v5, SFN f6, int v6);
    void Add(string name, SFN f1, int v1, SFN f2, int v2, SFN f3, int v3, SFN f4, int v4, SFN f5, int v5, SFN f6, int v6, SFN f7, int v7);
    void Add(string name, SFN f1, int v1, SFN f2, int v2, SFN f3, int v3, SFN f4, int v4, SFN f5, int v5, SFN f6, int v6, SFN f7, int v7, SFN f8, int v8);
public:
    vector<Skill> list;
    SkillRepository();
};

/*
     **스킬 종류 추가하는 공간**
     bool 로 쓸건 value1로 고정
*/

SkillRepository::SkillRepository() {
    Add("FastWalk1", BASE_MOVE_SPEED, 5);
    Add("FastWalk2", BASE_MOVE_SPEED, 10);
    Add("Carrier1", MAX_WEIGHT, 20);
}

/*
    여기까지
*/

void SkillRepository::Add(string name, SFN f1, int v1) {
    Stat stat;
    stat.AddStatFieldValue(f1, v1);
    list.push_back(Skill(name,stat));
}

void SkillRepository::Add(string name, SFN f1, int v1, SFN f2, int v2) {
    Stat stat;
    stat.AddStatFieldValue(f1, v1);
    stat.AddStatFieldValue(f2, v2);
    list.push_back(Skill(name, stat));
}

void SkillRepository::Add(string name, SFN f1, int v1, SFN f2, int v2, SFN f3, int v3) {
    Stat stat;
    stat.AddStatFieldValue(f1, v1);
    stat.AddStatFieldValue(f2, v2);
    stat.AddStatFieldValue(f3, v3);
    list.push_back(Skill(name, stat));
}

void SkillRepository::Add(string name, SFN f1, int v1, SFN f2, int v2, SFN f3, int v3, SFN f4, int v4) {
    Stat stat;
    stat.AddStatFieldValue(f1, v1);
    stat.AddStatFieldValue(f2, v2);
    stat.AddStatFieldValue(f3, v3);
    stat.AddStatFieldValue(f4, v4);
    list.push_back(Skill(name, stat));
}

void SkillRepository::Add(string name, SFN f1, int v1, SFN f2, int v2, SFN f3, int v3, SFN f4, int v4, SFN f5, int v5) {
    Stat stat;
    stat.AddStatFieldValue(f1, v1);
    stat.AddStatFieldValue(f2, v2);
    stat.AddStatFieldValue(f3, v3);
    stat.AddStatFieldValue(f4, v4);
    stat.AddStatFieldValue(f5, v5);
    list.push_back(Skill(name, stat));
}

void SkillRepository::Add(string name, SFN f1, int v1, SFN f2, int v2, SFN f3, int v3, SFN f4, int v4, SFN f5, int v5, SFN f6, int v6) {
    Stat stat;
    stat.AddStatFieldValue(f1, v1);
    stat.AddStatFieldValue(f2, v2);
    stat.AddStatFieldValue(f3, v3);
    stat.AddStatFieldValue(f4, v4);
    stat.AddStatFieldValue(f5, v5);
    stat.AddStatFieldValue(f6, v6);
    list.push_back(Skill(name, stat));
}

void SkillRepository::Add(string name, SFN f1, int v1, SFN f2, int v2, SFN f3, int v3, SFN f4, int v4, SFN f5, int v5, SFN f6, int v6, SFN f7, int v7) {
    Stat stat;
    stat.AddStatFieldValue(f1, v1);
    stat.AddStatFieldValue(f2, v2);
    stat.AddStatFieldValue(f3, v3);
    stat.AddStatFieldValue(f4, v4);
    stat.AddStatFieldValue(f5, v5);
    stat.AddStatFieldValue(f6, v6);
    stat.AddStatFieldValue(f7, v7);
    list.push_back(Skill(name, stat));
}

void SkillRepository::Add(string name, SFN f1, int v1, SFN f2, int v2, SFN f3, int v3, SFN f4, int v4, SFN f5, int v5, SFN f6, int v6, SFN f7, int v7, SFN f8, int v8) {
    Stat stat;
    stat.AddStatFieldValue(f1, v1);
    stat.AddStatFieldValue(f2, v2);
    stat.AddStatFieldValue(f3, v3);
    stat.AddStatFieldValue(f4, v4);
    stat.AddStatFieldValue(f5, v5);
    stat.AddStatFieldValue(f6, v6);
    stat.AddStatFieldValue(f7, v7);
    stat.AddStatFieldValue(f8, v8);
    list.push_back(Skill(name, stat));
}