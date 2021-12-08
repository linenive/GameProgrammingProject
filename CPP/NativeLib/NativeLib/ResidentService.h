#pragma once

#include "ObjectRepository.h"
#include "BuildingRepository.h"

class ResidentService {
private:
	ObjectService* object_service;
	ObjectRepository* object_repo;
	BuildingRepository* building_repo;

	void AssignCharacterToBuilding(Character* villager, int building_id) {
		Building* building = building_repo->GetBuildingById(building_id);
		building->AssignCharacter(villager);
	}

	void FreeFromExistHome(Character* resident) {
		if (HasHome(resident)) {
			Building* home = building_repo->GetBuildingById(resident->home_id);
			home->FreeResident(resident->GetId());
		}
	}

	bool HasHome(Character* resident) {
		return resident->home_id != -1;
	}

	void FreeFromExistWorkSpace(Character* resident) {
		if (HasWorkSpace(resident)) {
			Building* work_space = building_repo->GetBuildingById(resident->work_space_id);
			work_space->FreeResident(resident->GetId());
		}
	}

	bool HasWorkSpace(Character* resident) {
		return resident->work_space_id != -1;
	}

	bool IsInvalidRequest(int resident_id, int building_id) {
		if (object_repo->IsNotExistId(resident_id) || !building_repo->IsExistId(building_id)) {
			printf("WARNING: [ResidentService]Trying to access not exist IDs. ");
			printf("char ID : %d, building ID : %d\n", resident_id, building_id);
			return true;
		}
		return false;
	}

	bool IsInvalidRequest(int resident_id) {
		if (object_repo->IsNotExistId(resident_id)) {
			printf("WARNING: [ResidentService]Trying to access not exist ID. ");
			printf("char ID : %d\n", resident_id);
			return true;
		}
		return false;
	}

	Vector2 DummyVector() {
		return Vector2(10, 10);
	}

public:
	ResidentService(ObjectService* object_service, ObjectRepository* object_repo, BuildingRepository* building_repo)
		: object_service(object_service), object_repo(object_repo), building_repo(building_repo) {}
	
	bool AssignResidentToHome(int resident_id, int home_id) {
		if (IsInvalidRequest(resident_id))
			return false;
		if (home_id == -1)
			return false;

		Character* resident = object_repo->GetCharacter(resident_id);
		FreeFromExistHome(resident);

		resident->home_id = home_id;
		AssignCharacterToBuilding(resident, home_id);

		return true;
	}

	void AssignResidentToWorkSpace(int resident_id, int work_space_id) {
		if (IsInvalidRequest(resident_id, work_space_id))
			return;
		Character* resident = object_repo->GetCharacter(resident_id);
		FreeFromExistWorkSpace(resident);

		resident->work_space_id = work_space_id;
		AssignCharacterToBuilding(resident, work_space_id);
	}


	void FreeFromHome(int resident_id) {
		if (IsInvalidRequest(resident_id))
			return;
		Character* resident = object_repo->GetCharacter(resident_id);
		Building* home = building_repo->GetBuildingById(resident->home_id);

		home->FreeResident(resident_id);
		resident->home_id = -1;
	}

	void FreeFromWorkSpace(int resident_id) {
		if (IsInvalidRequest(resident_id))
			return;
		Character* resident = object_repo->GetCharacter(resident_id);
		Building* work_space = building_repo->GetBuildingById(resident->home_id);

		work_space->FreeResident(resident_id);
		resident->work_space_id = -1;
	}

	Vector2 GetResidentHomePosition(int resident_id) {
		if (IsInvalidRequest(resident_id))
			return DummyVector();
		Character* resident = object_repo->GetCharacter(resident_id);
		if (resident->home_id == -1) {
			printf("ERROR: [ResidentService]this resident doesn't have home! id: %d\n", resident_id);
			return DummyVector();
		}
		else {
			Building* home = building_repo->GetBuildingById(resident->home_id);
			return home->GetCenterPosition();
		}
	}

	Vector2 GetResidentWorkSpacePosition(int resident_id) {
		if (IsInvalidRequest(resident_id))
			return DummyVector();
		Character* resident = object_repo->GetCharacter(resident_id);
		if (resident->work_space_id == -1) {
			printf("ERROR: [ResidentService]this resident doesn't have work space! id: %d\n", resident_id);
			return DummyVector();
		}
		else {
			Building* work_space = building_repo->GetBuildingById(resident->work_space_id);
			return work_space->GetCenterPosition();
		}
	}

	bool RecruitGuestAsResident(int guest_id) {
		if (IsInvalidRequest(guest_id))
			return false;
		// To-do: check is home id valid?
		int home_id = building_repo->GetAssignableHouseId();
		if (home_id == -1)
			return false;
		Resident* new_resident = object_service->CreateNewResident(object_repo->GetCharacter(guest_id));
		object_service->DeleteCharacter(guest_id);
		AssignResidentToHome(new_resident->GetId(), home_id);

		return true;
	}

	Array GetRecruitableResidentArray() {
		map<int, Resident*>* residents = object_repo->GetResidents();
		Array result = Array();

		for (auto iter = residents->begin(); iter != residents->end(); ++iter) {

			if (iter->second->work_space_id != -1) {
				continue;
			}

			Dictionary resident_info = Dictionary();

			resident_info["character_id"] = iter->first;
			resident_info["name"] = iter->second->GetFullName().GetFullname().c_str();
			
			result.append(resident_info);
		}

		return result;
	}
};