#pragma once
#include "Common.h"

class Physics {
private:
	Transform2D transform;
	Vector2 scale;
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
};