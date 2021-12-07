#pragma once
#include "CoordinatesSystem.h"

// Todo: load DB
enum class ePurposeOfVisitType {
	Lodge,
	JustChilling,
	Recovery,
	Cure,
	Shopping,
	BuyLiquidMedicine,
	BuyFirewood,
};

class PurposeOfVisit {
private:
	ePurposeOfVisitType type;
	string name;
	bool is_done = false;

public:
	// To-do: 목적 수행이 가능한 지 확인
	bool CanExecute() {
		return false && is_done;
	}
	PurposeOfVisit(string _name, ePurposeOfVisitType _type)
		: name(_name), type(_type) {}
	string GetName() {
		return name;
	}
};


class Schedule {
protected:
	vector<PurposeOfVisit*> purpose_of_visits;
public:
	// 임시 함수
	bool IsHavePurpose() {
		return purpose_of_visits.size() != 0;
	}

	// 임시 함수
	string GetFirstPurpose() {
		return purpose_of_visits[0]->GetName();
	}
};

class GuestSchedule : public Schedule {
private:
	
	Coordinates village_arrival_point;
	Coordinates village_departure_point;

public:
	~GuestSchedule() {
		for (PurposeOfVisit* p : purpose_of_visits) {
			delete p;
		}
	}
	GuestSchedule(Coordinates _village_arrival_point, Coordinates _village_departure_point) :
		village_arrival_point(_village_arrival_point),
		village_departure_point(_village_departure_point) {}

	vector<PurposeOfVisit*> GetPurposOfVisit() {
		return purpose_of_visits;
	}
	void AddPurposeOfVisit(PurposeOfVisit*  new_purpose_of_visit) {
		purpose_of_visits.push_back(new_purpose_of_visit);
	}
	Coordinates GetVillageDeparturePoint() { return village_departure_point; }
};

class ResidentSchedule : public Schedule {

};