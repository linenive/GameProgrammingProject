#pragma once
#include "Common.h"
#include <Node2D.hpp>
#include "Camera.h"
#include "GameRule.h"

namespace godot {
	class CameraManager : public Node2D
	{
		GODOT_CLASS(CameraManager, Node2D);

	private:
		Camera camera;

		float zoom_max = 1.5;
		float zoom_min = 0.5;

		float zoom_scroll_factor = 0.2;
		
		Vector2 camera_boundary_interval = Vector2(1000, 1000);

		void CameraMoveWithKey(Vector2 velocity);
		void CameraMoveWithMouse(Vector2 now_mouse_vector);

		Vector2 CalcNewPosition(Vector2 new_position);

	public:
		float mouse_moving_bound_size;
		float camera_moving_speed = CAMERA_MOVING_SPEED;

		static void _register_methods();
		void _init();

		Vector2 GetCurrentCameraPosition() { return camera.GetPosition(); }
		void SetCurrentCameraPosition(Vector2 new_position) { camera.SetPosition(new_position); }

		void ZoomOut();
		void ZoomIn();

		float GetCurrentZoom() { return camera.GetZoomDegree(); }
		void SetCurrentZoom(float new_zoom);

		float GetCurrentZoomMax() { return zoom_max; }
		void SetCurrentZoomMax(float new_zoom_max) { zoom_max = new_zoom_max; }

		float GetCurrentZoomMin() { return zoom_min; }
		void SetCurrentZoomMin(float new_zoom_min) { zoom_min = new_zoom_min; }
	};
}