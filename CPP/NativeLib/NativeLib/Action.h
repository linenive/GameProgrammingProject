#pragma once
#include "WorldObject.h"

class Action{
protected:
	const Vector2 target;
public:
	Action(const Vector2 _target):target(_target){}
	virtual void ExecuteAction(WorldObject* performer) = 0;
	virtual bool IsEndAction(WorldObject* performer) = 0;
};

class MoveAction : public Action {
private:
	bool CheckArriveCurrentTarget(Vector2 current_position) {
		Vector2 current_distance = target - current_position;
		float distance = current_distance.length();
		// To-do: SLOWING_RADIUS �߸� ���ǰ� �ֱ⿡ ������. ���� �ٽ� �����ϱ�
		return (distance < CHARACTER_ARRIVE_RADIUS);
	}

public:
	MoveAction(const Vector2 _target):Action(_target){}
	virtual void ExecuteAction(WorldObject* performer) {
		Physics* physics = performer->GetPhysics();
		physics->CalculateVelocity(target);
		physics->UpdatePosition();
	}
	virtual bool IsEndAction(WorldObject* performer) {
		return CheckArriveCurrentTarget(performer->GetPhysics()->GetPosition());
	}
};