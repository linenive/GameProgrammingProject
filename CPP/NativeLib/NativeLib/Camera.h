#pragma once
#include "Common.h"
#include "GameRule.h"

class Camera {

private:	
	Vector2 current_position;
	float current_zoom = CAMERA_DEFAULT_ZOOM_DEGREE;
	
public:

	void CameraMove(Vector2 new_position){
		current_position = new_position;
	}

	virtual Vector2 GetPosition() {
		return current_position;
	}

	void SetPosition(Vector2 new_pos) {
		current_position = new_pos;
	}

	virtual float GetZoomDegree() {
		return current_zoom;
	}

	void SetZoomDegree(float new_zoom_degree) {
		current_zoom = new_zoom_degree;
	}
};