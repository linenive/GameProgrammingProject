#include "Common.h"
#include "GameManager.h"
#include "UIManager.h"
#include "WorldManager.h"
#include "InputManager.h"
#include "CameraManager.h"
#include "StaticUnitManager.h"
#include "InstanceUIManager.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options * o) {
	godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options * o) {
	godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void* handle) {
	godot::Godot::nativescript_init(handle);

	godot::register_class<GameManager>();
	godot::register_class<UIManager>();
	godot::register_class<WorldManager>();
	godot::register_class<InputManager>();
	godot::register_class<CameraManager>();
	godot::register_class<StaticUnitManager>();
	godot::register_class<InstanceUIManager>();
}
