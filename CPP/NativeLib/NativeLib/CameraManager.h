#pragma once
#include "Common.h"
#include <Node2D.hpp>

enum eCameraState { DEFAULT, TRACE };
namespace godot {
	class CameraManager : public Node2D
	{
		GODOT_CLASS(CameraManager, Node2D);

	private:
		Vector2 g_screen_size;
		Vector2 g_unmoving_size;
		Vector2 g_screen_boundary_lefttop;
		Vector2 g_screen_boundary_rightbottom;

		Vector2 g_velocity = Vector2();

		float g_speed = 3;
		float g_unmoving_interval = 100;

		float kzoom_in = 0.5;
		float kzoom_default = 1;
		float kzoom_scrollfactor = 0.2;
		float kzoom_max = 1.5;
		float kzoom_min = 0.5;


		void CameraMovewithKey();
		void CameraMovewithMouse(Vector2 nowmousevector);
		void InitCameraSetting();

		void ZoomOut(float now_zoom);
		void ZoomIn(float now_zoom);
		void Zoom(float zoomfactor);
	public:
		static void _register_methods();
		void _init();

		void SetLimit();
		void SetCameraSetting_Default();
		void SetCameraSetting_Trace(NodePath newtracing_path);

		eCameraState g_nowcamerastate;
		Node2D g_targetNode;
		NodePath g_nowtarget_path;
		Vector2 g_now_position;
		float g_now_scrollfactor;
	};
}