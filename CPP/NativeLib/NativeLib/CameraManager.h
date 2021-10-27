#pragma once
#include "Common.h"
#include <Node2D.hpp>

namespace godot {
	class CameraManager : public Node2D
	{
		GODOT_CLASS(CameraManager, Node2D);

	private:
		Vector2 g_mouse_moving_bound;
		Vector2 g_now_position;

		float g_now_zoom=1;

		float kzoom_scrollfactor = 0.2;
		float g_zoom_max = 1.5;
		float g_zoom_min = 0.5;

		void CameraMoveWithKey(Vector2 velocity);
		void CameraMoveWithMouse(Vector2 now_mouse_vector);
	public:
		float g_speed = 3;
		float g_mouse_moving_interval = 100;

		static void _register_methods();
		void _init();

		void SetMouseMovingBound();

		Vector2 GetNowCameraPosition() { return g_now_position; }
		void SetNowCameraPosition(Vector2 new_position) { g_now_position = new_position; }

		void ZoomOut();
		void ZoomIn();

		float GetNowZoom() { return g_now_zoom; }
		void SetNowZoom(float new_zoom);

		float GetNowZoomMax() { return g_zoom_max; }
		void SetNowZoomMax(float new_zoom_max) { g_zoom_max = new_zoom_max; }

		float GetNowZoomMin() { return g_zoom_min; }
		void SetNowZoomMin(float new_zoom_min) { g_zoom_min = new_zoom_min; }
	};
}