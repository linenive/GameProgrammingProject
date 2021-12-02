#pragma once
#include "StaticUnit.h"
#include "StructureType.h"

class Structure : public StaticUnit {

public:
	eStructureType type;
	Structure(int id, eStructureType _type, string name, Rect2 _ocupation_area)
		: StaticUnit(id, name, _ocupation_area), type(_type){}
};