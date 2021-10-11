#pragma once
#include "Common.h"
#include <CanvasLayer.hpp>

namespace godot {
	class CameraManager : public CanvasLayer
	{
		GODOT_CLASS(CameraManager, CanvasLayer);

	private:

		float screenBounds_left;
		float screenBounds_right;
		float screenBounds_up;
		float screenBounds_down;
		void DetectScreenBounds(Vector2 newScreenSize);
	public:
		static void _register_methods();
		void _init();

		void SetScreenSize(Vector2 nowScreenSize);
		void SetTarget(Vector2 pos);
		void ReleaseTarget(Vector2 pos);
	};
}