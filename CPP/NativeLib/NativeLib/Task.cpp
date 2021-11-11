#include "Task.h"
#include <cmath>

Vector2 UpdateVelocityBySeek(Physics performer_physics, Vector2 target) {
	return (target - performer_physics.getPosition()).normalized() * performer_physics.max_velocity;
}

Physics UpdatePosition(Physics performer_physics) {
	Vector2 new_position = performer_physics.getPosition() + performer_physics.velocity;
	performer_physics.setPosition(new_position);
	return performer_physics;
}
Vector2 Truncate(Vector2 velocity, float max) {
	float i = max / velocity.length();
	i = min(i, 1.0f);
	return velocity * i;
}

void Task::SetTarget(Vector2 new_target){
	target = new_target; 
}

void Task::ExecuteTask(WorldObject* performer){
	Physics performer_physics = performer->GetPhysics();

	Vector2 desired_velocity = UpdateVelocityBySeek(performer_physics, target);
	Vector2 steering = desired_velocity - performer_physics.velocity;
	
	steering = Truncate(steering, CHARACTER_MAX_FORCE);
	steering = steering / performer_physics.mass;

	performer_physics.velocity = Truncate(performer_physics.velocity + steering, CHARACTER_MAX_VELOCITY);
	
	Vector2 now_distance = target - performer_physics.getPosition();
	float distance = now_distance.length();
	if (distance > CHARACTER_SLOWING_RADIUS)
		performer->SetPhysics(UpdatePosition(performer_physics));
}
