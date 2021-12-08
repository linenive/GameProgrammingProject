#pragma once
#include "Common.h"
#include <algorithm>

class Physics {
private:
	Transform2D transform;
	Vector2 scale;

	Vector2 Truncate(Vector2 velocity, float max) {
		float i = max / velocity.length();
		i = min(i, 1.0f);
		return velocity * i;
	}

	Vector2 UpdateVelocityBySeek(Vector2 target) {
		return (target - GetPosition()).normalized() * max_velocity;
	}

public:
	float mass = 10;
	Vector2 velocity;
	Vector2 max_velocity;

	Physics(Transform2D _transform, Vector2 _scale)
		:transform(_transform), scale(_scale), velocity(Vector2(0, 0))
		, max_velocity(Vector2(CHARACTER_MAX_VELOCITY, CHARACTER_MAX_VELOCITY)){}

	Vector2 GetPosition() {
		return transform.get_origin();
	}

	void SetPosition(Vector2 pos) {
		transform.set_origin(pos);
	}

	Transform2D GetTransform() {
		return transform;
	}

	Vector2 GetScale() {
		return scale;
	}

	Rect2 GetRect() {
		return Rect2(
			transform.get_origin().x - scale.x / 2,
			transform.get_origin().y - scale.y / 2,
			scale.x,
			scale.y
		);
	}

	void CalculateVelocity(Vector2 target, int speed_factor) {
		Vector2 desired_velocity = UpdateVelocityBySeek(target);
		Vector2 steering = desired_velocity - velocity;

		steering = Truncate(steering, CHARACTER_MAX_FORCE);
		steering = steering / mass;

		velocity = Truncate(velocity * 0.1f + steering, CHARACTER_MAX_VELOCITY);
		velocity *= speed_factor;
		velocity /= 10;
	}

	void UpdatePosition() {
		SetPosition(GetPosition() + velocity);
	}
};