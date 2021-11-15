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

void Task::ChangeTarget(vector<Vector2> new_path_list, Vector2 new_target){//Vector2 new_target){//
	now_moving = false;

	task_target = new_target;
	path_list = new_path_list;

	now_path_list_length = path_list.size();
	now_path_index = -1;
	now_moving = CanChangeNextPos();
}

bool Task::CanChangeNextPos() {
	if (++now_path_index < now_path_list_length) {
		now_target = path_list[now_path_index];
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
	if (now_moving == false) return;
	
	Physics new_physics = CalcPhysics(performer->GetPhysics(), now_target);

	if (ArriveNowTarget(new_physics.getPosition())) {
		now_moving = CanChangeNextPos();
	}
	else {
		performer->SetPhysics(UpdatePosition(new_physics));
	}
}

bool Task::ArriveNowTarget(Vector2 now_position) {
	Vector2 now_distance = now_target - now_position;
	float distance = now_distance.length();

	if (distance < CHARACTER_SLOWING_RADIUS) return true;
	else return false;

}
