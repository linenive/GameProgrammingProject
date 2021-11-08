#include "Task.h"

Vector2 UpdateVelocityBySeek(Physics performer_physics, Vector2 target) {
	return (target - performer_physics.GetPosition()).normalized() * performer_physics.max_velocity;
}

Physics UpdatePosition(Physics performer_physics) {
	Vector2 new_position = performer_physics.GetPosition() + performer_physics.velocity;
	performer_physics.SetPosition(new_position);
	return performer_physics;
}

void Task::ExecuteTask(WorldObject* performer){
	Physics performer_physics = performer->GetPhysics();

	performer_physics.velocity = UpdateVelocityBySeek(performer_physics, target);

	// To-do: steering 계산 여기에서
	
	performer->SetPhysics(UpdatePosition(performer_physics));
}