#pragma once

class InstanceUI {
private :
	int character_id;
	int ui_type;

	float target_value;
	float current_value;
public:
	InstanceUI(float _target_value, float _start_value) :target_value(_target_value), current_value(_start_value) {
	}
	
	void Update(float new_cur) {
		current_value = new_cur;
	}

	bool DetectUIDisappear() {
		if (current_value <= target_value) {
			return true;
		}
		return false;
	}
	int GetCharacterID() { return character_id; }
	int GetUIType() { return ui_type; }
	int GetCurrentValue() { return current_value; }

};