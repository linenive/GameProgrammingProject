#ifndef GODOT_CPP_SEMAPHORE_HPP
#define GODOT_CPP_SEMAPHORE_HPP


#include <gdnative_api_struct.gen.h>
#include <stdint.h>

#include <core/CoreTypes.hpp>
#include <core/Ref.hpp>

#include "Reference.hpp"
namespace godot {


class Semaphore : public Reference {
	struct ___method_bindings {
		godot_method_bind *mb_post;
		godot_method_bind *mb_wait;
	};
	static ___method_bindings ___mb;
	static void *_detail_class_tag;

public:
	static void ___init_method_bindings();
	inline static size_t ___get_id() { return (size_t)_detail_class_tag; }

	static inline const char *___get_class_name() { return (const char *) "Semaphore"; }
	static inline const char *___get_godot_class_name() { return (const char *) "Semaphore"; }
	static inline Object *___get_from_variant(Variant a) { godot_object *o = (godot_object*) a; return (o) ? (Object *) godot::nativescript_1_1_api->godot_nativescript_get_instance_binding_data(godot::_RegisterState::language_index, o) : nullptr; }

	// enums

	// constants


	static Semaphore *_new();

	// methods
	Error post();
	Error wait();

};

}

#endif