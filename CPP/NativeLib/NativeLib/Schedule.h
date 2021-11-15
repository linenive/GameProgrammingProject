#pragma once
#include <vector>
#include "Task.h"
#include "CoordinatesSystem.h"

// Todo: load DB
enum class PurposeOfVisitType {
	Lodge,
	JustChilling,
	Recovery,
	Cure,
	Shopping,
	BuyLiquidMedicine
};

class PurposeOfVisit {
private:
	PurposeOfVisitType type;
	string name;
	bool is_done = false;

public:
	// To-do: 목적 수행이 가능한 지 확인
	bool CanExecute() {
		return false && is_done;
	}
	PurposeOfVisit(string _name, PurposeOfVisitType _type)
		: name(_name), type(_type) {}
};


class Schedule {
protected:
	Coordinates village_arrival_point;
	Coordinates village_departure_point;
	Task* currentTask;
public:
	~Schedule() {
		if(currentTask != nullptr)
			delete currentTask;
	}
	Schedule():currentTask(nullptr){
	
	}
	Task* GetTask() { return currentTask; }
	void SetTask(Task* new_task) { currentTask = new_task; }
	bool HasTask() { return currentTask != nullptr; }
	Coordinates GetVillageDeparturePoint() { return village_departure_point; }
};

class GuestSchedule : public Schedule {
private:
	vector<PurposeOfVisit> purpose_of_visits;

public:
	vector<PurposeOfVisit> GetPurposOfVisit() {
		return purpose_of_visits;
	}
};
