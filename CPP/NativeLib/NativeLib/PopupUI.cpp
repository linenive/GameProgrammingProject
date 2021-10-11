#include "PopupUI.h"
#include <Input.hpp>
#include <InputEventMouseButton.hpp>
#include <GlobalConstants.hpp>

void PopupUI::_register_methods() {
	register_method("_init", &PopupUI::_init);
	//register_method("_input", &PopupUI::_input);
	register_method("_process", &PopupUI::_process);
	register_method("Pop", &PopupUI::Pop);
	register_method("MoveToFirst", &PopupUI::MoveToFirst);
	register_method("OnMouseEnter", &PopupUI::OnMouseEnter);
	register_method("OnMouseExit", &PopupUI::OnMouseExit);
}

void PopupUI::_init() {
	connect("_on_PopupUI_mouse_entered", this, "OnMouseEnter");
	connect("_on_PopupUI_mouse_exited", this, "OnMouseExit");
}

void PopupUI::Pop() {
	Godot::print("Heyhey" + get_name());
	show();
}

void PopupUI::MoveToFirst() {
	get_owner()->move_child(this, 0);
}

/*
void PopupUI::_input(Variant event)
{
	//Ref<InputEventMouseButton> mouse_btn = event;
	//if (mouse_btn->is_pressed())
		//Godot::print("Pressed Triangle");
}
*/

void PopupUI::OnMouseEnter() {
	is_mouse_enter = true;
	Godot::print("awfeafefw");
}

void PopupUI::OnMouseExit() {
	is_mouse_enter = false;
}

void PopupUI::_process(float delta)
{
	Input* input = Input::get_singleton();
	if (input->is_mouse_button_pressed(GlobalConstants::BUTTON_LEFT) && is_mouse_enter == true)
	{
		Godot::print(get_name() + " Pressed X");
	}
}
