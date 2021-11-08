#pragma once

class InputStatus {
public:
	bool is_dragging;
	Vector2 drag_start_point;
	Vector2 now_mouse_point;
	bool is_tile_highlighting;
	Rect2 tile_highlight;

	void ResetDrag() {
		is_dragging = false;
		drag_start_point = Vector2(0, 0);
	}
};

class ControlState {
protected:
	InputStatus* input;
	GameWorldForInput* world;

	void StartDrag(Vector2 start_pos) {
		input->drag_start_point = start_pos;
		input->is_dragging = true;
	}

	void EndDrag(Vector2 end_pos) {
		input->is_dragging = false;
	}

	int GetTileIDIfMouseHoverTileMap(Vector2 mouse_position) {
		if (world->GetTileMap()->CheckTileInVector2(mouse_position)) {
			return world->GetTileMap()->GetTileIdByVector2(mouse_position);
		}
		else {
			return -1;
		}
	}

public:
	virtual void MouseHover(Vector2 position) = 0;
	virtual void MouseClick(Vector2 position) = 0;
	virtual void MouseRelease(Vector2 position) = 0;
	virtual void Reset() = 0;
	void SetInputStatus(InputStatus* _input) { input = _input; }
	void SetGameWorld(GameWorldForInput* _world) { world = _world; }
};

class NormalState : public ControlState {
	void MouseHover(Vector2 mouse_position) override {
	}

	void MouseClick(Vector2 mouse_position) override {
		Godot::print("[NormalState]Mouse Click: " + mouse_position);
		StartDrag(mouse_position);
	}

	void MouseRelease(Vector2 mouse_position) override {
		Godot::print("[NormalState]Mouse Release: " + mouse_position);
		EndDrag(mouse_position);
	}
	void Reset() {
		input->ResetDrag();
	}
};

class BuildState : public ControlState {
private:
	void HighlightHoverdTile(Vector2 mouse_position) {
		int hovered_tile_id = GetTileIDIfMouseHoverTileMap(mouse_position);
		if (hovered_tile_id >= 0) {
			Tile hoverd_tile = world->GetTileMap()->GetTile(hovered_tile_id);
			input->is_tile_highlighting = true;
			input->tile_highlight = hoverd_tile.GetPhysics().GetRect();
		}
		else {
			input->is_tile_highlighting = false;
		}
	}
public:
	void MouseHover(Vector2 mouse_position) override {
		HighlightHoverdTile(mouse_position);
	}

	void MouseClick(Vector2 mouse_position) override {
		Godot::print("[BuildState]Mouse Click: " + mouse_position);
	}

	void MouseRelease(Vector2 mouse_position) override {
		Godot::print("[BuildState]Mouse Release: " + mouse_position);
	}

	void Reset() {
		input->is_tile_highlighting = false;
	}
};

class ControlContext {
private:
	ControlState* state;
	InputStatus input;
	GameWorldForInput* world;
public:
	ControlContext()
		: state(new NormalState()){
		state->SetInputStatus(&input);
	}
	~ControlContext() { if (state) delete state; }

	void SetGameWorld(GameWorldForInput* _world) {
		world = _world;
	}

	void SetState(ControlState* new_state) {
		if (state) {
			state->Reset();
			delete state;
		}
		state = new_state;
		state->SetInputStatus(&input);
		state->SetGameWorld(world);
	}

	void MouseHover(Vector2 mouse_position) {
		state->MouseHover(mouse_position);
	}

	void MouseClick(Vector2 mouse_position) {
		state->MouseClick(mouse_position);
	}

	void MouseRelease(Vector2 mouse_position) {
		state->MouseRelease(mouse_position);
	}

	InputStatus GetInputStatus() {
		return input;
	}
};
