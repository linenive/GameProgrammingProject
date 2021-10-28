#pragma once
#include "Common.h"

class Physics {
private:
	Transform2D transform;
public:
	float mass;
	Vector2 velocity;
	Vector2 max_velocity;

	Physics(Transform2D transform){
		this->transform = transform;
		velocity = Vector2(0, 0);
		mass = 10;
		max_velocity = Vector2(CHARACTER_MAX_VELOCITY, CHARACTER_MAX_VELOCITY);
	}

	Vector2 getPosition() {
		return transform.get_origin();
	}

	void setPosition(Vector2 pos) {
		transform.set_origin(pos);
	}

	Transform2D getTransform() {
		return transform;
	}
};