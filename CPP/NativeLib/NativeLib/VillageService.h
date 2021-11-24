#pragma once

#include "VillageRepository.h"

class VillageService {
private:
	VillageRepository* village_repo;

public:
	VillageService(VillageRepository* _village_repo) : village_repo(_village_repo) {}

	String GetVillageName() {
		return village_repo->GetVillage()->GetVillageName().c_str();
	}

	void SetVillageName(String new_name) {
		village_repo->GetVillage()->SetVillageName(new_name.utf8().get_data());
	}

	int GetMoney() {
		village_repo->GetVillage()->GetMoney();
	}
};