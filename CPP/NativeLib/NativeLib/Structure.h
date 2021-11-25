#pragma once
#include "StaticUnit.h"

class Structure : public StaticUnit {

public:
	Structure(int id, string name, Rect2 _ocupation_area)
		: StaticUnit(id, name, _ocupation_area) {}
};