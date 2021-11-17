#pragma once
#include "StaticUnit.h"

// �ӽ�
enum eStructureType {
	A, B, C, D
};

class Structure : public StaticUnit {
private:
	eStructureType type;
public:
	Structure(int id, string name, Rect2 _ocupation_area, eStructureType type)
		: StaticUnit(id, name, _ocupation_area), type(type) {}

};