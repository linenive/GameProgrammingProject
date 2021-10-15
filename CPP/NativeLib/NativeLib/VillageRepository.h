#pragma once
#include "Village.h"

class VillageRepository {
private:
	Village* village;

public:
	VillageRepository() {
		village = new Village("new village");
	}
	Village* GetVillage() { return village; }
};