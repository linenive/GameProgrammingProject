#include "Task.h"
#include <algorithm>

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

void Task::ChangeTarget(vector<Vector2> new_path_list, Vector2 new_target){
	current_moving = false;

	task_target = new_target;
	path_list = new_path_list;

	current_path_list_length = path_list.size();
	current_path_index = -1;
	current_moving = CanChangeNextPos();
}

bool Task::CanChangeNextPos() {
	if (++current_path_index < current_path_list_length) {
		current_target = path_list[current_path_index];
		Godot::print("[Task] new target: " + current_target);
		return true;
	}
	return false;
}
Physics CalcPhysics(Physics performer_physics, Vector2 target) {
	Vector2 desired_velocity = UpdateVelocityBySeek(performer_physics, target);
	Vector2 steering = desired_velocity - performer_physics.velocity;

	steering = Truncate(steering, CHARACTER_MAX_FORCE);
	steering = steering / performer_physics.mass;

	performer_physics.velocity = Truncate(performer_physics.velocity + steering, CHARACTER_MAX_VELOCITY);

	return performer_physics;
}

void Task::ExecuteTask(WorldObject* performer){
	if (current_moving == false) return;
	
	Physics new_physics = CalcPhysics(performer->GetPhysics(), current_target);

	if (ArriveCurrentTarget(new_physics.GetPosition())) {
		current_moving = CanChangeNextPos();
	}
	else {
		performer->SetPhysics(UpdatePosition(new_physics));
	}
}

bool Task::ArriveCurrentTarget(Vector2 current_position) {
	Vector2 current_distance = current_target - current_position;
	float distance = current_distance.length();

	if (distance < CHARACTER_SLOWING_RADIUS) return true;
	else return false;

}
