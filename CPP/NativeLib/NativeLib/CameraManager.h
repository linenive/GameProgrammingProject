#pragma once
#include "Common.h"
#include <Camera2D.hpp>

namespace godot {
	class CameraManager : public Camera2D
	{
		GODOT_CLASS(CameraManager, Camera2D);

	private:
		Vector2 nowAddVector;
		float screenBounds_left;
		float screenBounds_right;
		float screenBounds_up;
		float screenBounds_down;
		void DetectScreenBounds(Vector2 newScreenSize);
	public:
		static void _register_methods();

		Vector2 GetAddVector() { return nowAddVector; }
		void SetScreenSize(Vector2 nowScreenSize);
		void CameraMove_Left();
		void CameraMove_Right();
		void CameraMove_Up();
		void CameraMove_Down();
	};
}