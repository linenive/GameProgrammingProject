#pragma once
#include <string>
using namespace std;

enum class eNameType {
    MAN,
    WOMAN
};

class CharacterName {
public:
    string value;
    eNameType type;
    CharacterName(string _value, eNameType _type) : value(_value), type(_type) {};
    bool operator==(CharacterName& other);
};

class CharacterFullName {
private:
    string familyName;
    CharacterName name;

public:
    CharacterFullName(string familyName, CharacterName name) : familyName(familyName), name(name) {};

    string GetFullname();
    CharacterName GetName();
    eNameType GetType();
};