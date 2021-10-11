#pragma once
#include "Common.h"
#include <WindowDialog.hpp>
#include <Button.hpp>
#include <InputEventMouseButton.hpp>

class PopupUI : public WindowDialog {
	GODOT_CLASS(PopupUI, WindowDialog);

private:
	bool is_mouse_enter = false;

public:
	static void _register_methods();

	void _init();
	//void _input(Variant event);
	void _process(float delta);
	void OnMouseEnter();
	void OnMouseExit();


	void Pop();

	void MoveToFirst();
};