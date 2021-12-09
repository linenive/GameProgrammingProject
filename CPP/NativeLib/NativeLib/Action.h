#pragma once
#include "Character.h"
#include "WorldObject.h"
#include "WorkType.h"

class Action{
public:
	virtual void ExecuteAction(Character* performer) = 0;
	virtual bool IsEndAction(Character* performer) = 0;
};

class MoveAction : public Action {
protected:
	const Vector2 target;
private:
	bool CheckArriveCurrentTarget(Vector2 current_position) {
		Vector2 current_distance = target - current_position;
		float distance = current_distance.length();
		// To-do: SLOWING_RADIUS �߸� ���ǰ� �ֱ⿡ ������. ���� �ٽ� �����ϱ�
		return (distance < CHARACTER_ARRIVE_RADIUS);
	}

public:
	MoveAction(const Vector2 _target):target(_target){
	}
	virtual void ExecuteAction(Character* performer) {
		performer->GetPhysics()->CalculateVelocity(target, performer->GetStatValue(eStatFieldType::BASE_MOVE_SPEED));
		performer->GetPhysics()->UpdatePosition();
	}
	virtual bool IsEndAction(Character* performer) {
		return CheckArriveCurrentTarget(performer->GetPhysics()->GetPosition());
	}
};

class PauseAction : public Action {
public:
	virtual void ExecuteAction(Character* performer) {

	}
	virtual bool IsEndAction(Character* performer) {
		return false;
	}
};

class WorkAction : public Action {
private:
	float left_time;
	eWorkType work_type;
	Inventory* target_inventory;

	bool IsEndAction() {
		return left_time <= 0;
	}
public:
	WorkAction(eWorkType _work_type, Inventory* target_inventory, float time_to_finish)
		: left_time(time_to_finish), target_inventory(target_inventory), work_type(_work_type) {
	}
	virtual void ExecuteAction(Character* performer) {
		if (IsEndAction()) {
			printf("WARNING: [WorkAction] IsEndAction had not been checked before execution\n");
			return;
		}
		int work_speed = performer->GetStatValue(WorkType::ToStatFieldType(work_type));
		left_time -= work_speed / 100; //To-do not 100 always maybe
		if (IsEndAction()) {
			printf("Got Item\n");
			Item item = *ItemDictionary::GetInstance()->GetItemByName(
				WorkType::ItemNameOf(work_type)
			);
			target_inventory->AddItem(
				*ItemDictionary::GetInstance()->GetItemByName(
					WorkType::ItemNameOf(work_type)
				),
				1
			);
			if (work_type == eWorkType::CREATE_ITEM) {
				target_inventory->PopItemById(1, 5); //sorry for hardcoding T.T
			}
		}
	}

	virtual bool IsEndAction(Character* performer) {
		return IsEndAction();
	}

	float GetLeftTime() {
		return left_time;
	}
};