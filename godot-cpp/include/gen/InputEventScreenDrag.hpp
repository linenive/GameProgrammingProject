#ifndef GODOT_CPP_INPUTEVENTSCREENDRAG_HPP
#define GODOT_CPP_INPUTEVENTSCREENDRAG_HPP


#include <gdnative_api_struct.gen.h>
#include <stdint.h>

#include <core/CoreTypes.hpp>
#include <core/Ref.hpp>

#include "InputEvent.hpp"
namespace godot {


class InputEventScreenDrag : public InputEvent {
	struct ___method_bindings {
		godot_method_bind *mb_get_index;
		godot_method_bind *mb_get_position;
		godot_method_bind *mb_get_relative;
		godot_method_bind *mb_get_speed;
		godot_method_bind *mb_set_index;
		godot_method_bind *mb_set_position;
		godot_method_bind *mb_set_relative;
		godot_method_bind *mb_set_speed;
	};
	static ___method_bindings ___mb;
	static void *_detail_class_tag;

public:
	static void ___init_method_bindings();
	inline static size_t ___get_id() { return (size_t)_detail_class_tag; }

	static inline const char *___get_class_name() { return (const char *) "InputEventScreenDrag"; }
	static inline const char *___get_godot_class_name() { return (const char *) "InputEventScreenDrag"; }
	static inline Object *___get_from_variant(Variant a) { godot_object *o = (godot_object*) a; return (o) ? (Object *) godot::nativescript_1_1_api->godot_nativescript_get_instance_binding_data(godot::_RegisterState::language_index, o) : nullptr; }

	// enums

	// constants


	static InputEventScreenDrag *_new();

	// methods
	int64_t get_index() const;
	Vector2 get_position() const;
	Vector2 get_relative() const;
	Vector2 get_speed() const;
	void set_index(const int64_t index);
	void set_position(const Vector2 position);
	void set_relative(const Vector2 relative);
	void set_speed(const Vector2 speed);

};

}

#endif