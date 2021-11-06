#pragma once

class InputStatus {
public:
	bool is_dragging;
	Vector2 drag_start_point;
	Vector2 now_mouse_point;

	void ResetDrag() {
		is_dragging = false;
		drag_start_point = Vector2(0, 0);
	}
};

class ControlState {
protected:
	InputStatus* input;
	void StartDrag(Vector2 start_pos) {
		input->drag_start_point = start_pos;
		input->is_dragging = true;
	}

	void EndDrag(Vector2 end_pos) {
		input->is_dragging = false;
	}

public:
	virtual void MouseHover(Vector2 position) = 0;
	virtual void MouseClick(Vector2 position) = 0;
	virtual void MouseRelease(Vector2 position) = 0;
	virtual void Reset() = 0;
	void SetInputStatus(InputStatus* _input) { input = _input; }
};

class NormalState : public ControlState {
	void MouseHover(Vector2 position) override {

	}

	void MouseClick(Vector2 position) override {
		Godot::print("[NormalState]Mouse Click: " + position);
		StartDrag(position);
	}

	void MouseRelease(Vector2 position) override {
		Godot::print("[NormalState]Mouse Release: " + position);
		EndDrag(position);
	}
	void Reset() {
		input->ResetDrag();
	}
};

class BuildState : public ControlState {
	void MouseHover(Vector2 position) override {

	}

	void MouseClick(Vector2 position) override {
		Godot::print("[BuildState]Mouse Click: " + position);
	}

	void MouseRelease(Vector2 position) override {
		Godot::print("[BuildState]Mouse Release: " + position);
	}

	void Reset() {

	}
};

class ControlContext {
private:
	ControlState* state;
	InputStatus input;
public:
	ControlContext() : state(new NormalState()) {
		state->SetInputStatus(&input);
	}
	~ControlContext() { if (state) delete state; }

	void SetState(ControlState* new_state) {
		if (state) {
			state->Reset();
			delete state;
		}
		state = new_state;
		state->SetInputStatus(&input);
	}

	void MouseHover(Vector2 position) {
		state->MouseHover(position);
	}

	void MouseClick(Vector2 position) {
		state->MouseClick(position);
	}

	void MouseRelease(Vector2 position) {
		state->MouseRelease(position);
	}

	bool IsDragging() {
		return input.is_dragging;
	}

	Vector2 GetDragStartPoint() {
		return input.drag_start_point;
	}
};
