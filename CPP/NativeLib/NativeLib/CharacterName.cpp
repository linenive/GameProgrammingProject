#include "CharacterName.h"

bool CharacterName::operator==(CharacterName& other) {
    return value == other.value && type == other.type;
}

string CharacterFullName::GetFullname() {
    return familyName + " " + name.value;
}

string CharacterFullName::GetLastname()
{
    return familyName;
}

CharacterName CharacterFullName::GetName(){
    return name;
}

eNameType CharacterFullName::GetType()
{
    return name.type;
}