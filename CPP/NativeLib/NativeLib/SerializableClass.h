#pragma once

#include "Common.h"
#include <list>
#include <vector>

class SerializableClass {
public:
	virtual Array Serialize() = 0;
};
