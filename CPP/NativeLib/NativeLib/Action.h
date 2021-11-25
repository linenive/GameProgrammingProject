#pragma once
#include "WorldObject.h"

class Action{
protected:
	const Vector2 target;
public:
	Action(const Vector2 _target):target(_target){}
	virtual void ExecuteAction(Physics* performer_physics) = 0;
	virtual bool IsEndAction(Physics* performer_physics) = 0;
};

class MoveAction : public Action {
private:
	bool CheckArriveCurrentTarget(Vector2 current_position) {
		Vector2 current_distance = target - current_position;
		float distance = current_distance.length();
		// To-do: SLOWING_RADIUS 잘못 사용되고 있기에 제거함. 이후 다시 구현하기
		return (distance < CHARACTER_ARRIVE_RADIUS);
	}

public:
	MoveAction(const Vector2 _target):Action(_target){
	}
	virtual void ExecuteAction(Physics* performer_physics) {
		performer_physics->CalculateVelocity(target);
		performer_physics->UpdatePosition();
	}
	virtual bool IsEndAction(Physics* performer_physics) {
		return CheckArriveCurrentTarget(performer_physics->GetPosition());
	}
};