#pragma once
#include "StaticObject.h"

// юс╫ц
enum eStructureType {
	A, B, C, D
};

class Structure : public StaticObject{
private:
	eStructureType type;
public:
	Structure(string name, Rect2 _ocupation_area, eStructureType type)
		: StaticObject(name, _ocupation_area), type(type){}

};