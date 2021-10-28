#include "Task.h"
#include <cmath>

Vector2 UpdateVelocityBySeek(Physics performer_physics, Vector2 target) {
	return (target - performer_physics.GetPosition()).normalized() * performer_physics.max_velocity;
}
Physics UpdatePosition(Physics performer_physics) {
	Vector2 new_position = performer_physics.GetPosition() + performer_physics.velocity;
	performer_physics.SetPosition(new_position);
	return performer_physics;
}
Vector2 Truncate(Vector2 velocity, float max) {
	float i = max / velocity.length();
	i = min(i, 1.0f);
	return velocity * i;
}

void Task::ExecuteTask(WorldObject* performer){
	Physics performer_physics = performer->GetPhysics();

	Vector2 desired_velocity = UpdateVelocityBySeek(performer_physics, target);
	Vector2 steering = desired_velocity - performer_physics.velocity;
	
	steering = Truncate(steering, CHARACTER_MAX_FORCE);
	steering = steering / performer_physics.mass;

	performer_physics.velocity = Truncate(performer_physics.velocity + steering, CHARACTER_MAX_VELOCITY);
	
	performer->SetPhysics(UpdatePosition(performer_physics));
}
