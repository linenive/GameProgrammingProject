#pragma once

#include "VillageRepository.h"

class VillageService {
private:
	UIService* ui_service;
	VillageRepository* village_repo;

public:
	VillageService(UIService* _ui_service, VillageRepository* _village_repo) : ui_service(_ui_service), village_repo(_village_repo) {}

	String GetVillageName() {
		return village_repo->GetVillage()->GetVillageName().c_str();
	}

	void SetVillageName(String new_name) {
		village_repo->GetVillage()->SetVillageName(new_name.utf8().get_data());
	}

	int GetMoney() {
		return village_repo->GetVillage()->GetMoney();
	}

	void IncreaseMoney(int value, Vector2 occur_position) {
		ui_service->money_alert_effects.push(make_pair(value, occur_position));
		Village* vllage = village_repo->GetVillage();
		return vllage->SetMoney(vllage->GetMoney() + value);
	}

	void DecreaseMoney(int value, Vector2 position) {
		ui_service->money_alert_effects.push(make_pair(-value, position));
		Village* vllage = village_repo->GetVillage();
		return vllage->SetMoney(vllage->GetMoney() - value);
	}
};