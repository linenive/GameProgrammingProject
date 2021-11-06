#pragma once
#include "WorldObject.h"

// юс╫ц
enum eStructureType {
	A, B, C, D
};

class Structure : public WorldObject{
private:
	eStructureType type;
public:
	Structure(string name, Transform2D transform, Vector2 new_scale, eStructureType type)
		: WorldObject(name, transform, new_scale), type(type){}

};