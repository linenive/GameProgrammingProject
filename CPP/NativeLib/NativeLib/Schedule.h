#pragma once
#include "Task.h"
#include "CoordinatesSystem.h"
#include "Physics.h"

// Todo: load DB
enum class ePurposeOfVisitType {
	Lodge,
	JustChilling,
	Recovery,
	Cure,
	Shopping,
	BuyLiquidMedicine
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
};


class Schedule {
protected:
	Coordinates village_arrival_point;
	Coordinates village_departure_point;
	Task* task = nullptr;

	bool is_pause_for_dequeue = false;

public:
	~Schedule() {
		delete task;
	}
	Schedule() {

	}
	Schedule(Coordinates _village_arrival_point, Coordinates _village_departure_point) :
		village_arrival_point(_village_arrival_point),
		village_departure_point(_village_departure_point){}

	bool HasTask() {
		return task != nullptr;
	}

	void SetTask(Task* new_task) {
		task = new_task;
	}

	void DeleteTask() {
		delete task;
		task = nullptr;
	}

	bool IsTaskType(eTaskType type) {
		return task->GetType() == type;
	}

	bool IsTaskEnd() {
		return !task->HasAction();
	}

	void ExecuteTask(Physics* performer_physics) {
		task->Execute(performer_physics);
	}

	bool IsPauseForDequeue() { return is_pause_for_dequeue; }

	void PauseForDequeue() { is_pause_for_dequeue = true; }
	
	Coordinates GetVillageDeparturePoint() { return village_departure_point; }
};

class GuestSchedule : public Schedule {
private:
	vector<PurposeOfVisit*> purpose_of_visits;

public:
	~GuestSchedule() {
		for (PurposeOfVisit* p : purpose_of_visits) {
			delete p;
		}
	}
	GuestSchedule(Coordinates _village_arrival_point, Coordinates _village_departure_point) :
		Schedule(_village_arrival_point, _village_departure_point) {}
	vector<PurposeOfVisit*> GetPurposOfVisit() {
		return purpose_of_visits;
	}
	void AddPurposeOfVisit(PurposeOfVisit*  new_purpose_of_visit) {
		purpose_of_visits.push_back(new_purpose_of_visit);
	}
};
