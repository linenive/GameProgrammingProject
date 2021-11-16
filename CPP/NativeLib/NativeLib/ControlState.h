#pragma once

class InputStatus {
public:
	bool is_dragging = false;
	Vector2 drag_start_point;
	Vector2 now_mouse_point;
	bool is_area_highlighted = false;
	Rect2 highlighted_area;

	void ResetDrag() {
		is_dragging = false;
		drag_start_point = Vector2(0, 0);
	}
};

class ControlState {
protected:
	InputStatus input;
	GameWorldForInput* world;

	void StartDrag(Vector2 start_pos) {
		input.drag_start_point = start_pos;
		input.is_dragging = true;
	}

	void EndDrag(Vector2 end_pos) {
		input.is_dragging = false;
	}

	int GetTileIDIfMouseHoverTileMap(Vector2 mouse_position) {
		return world->GetTileMap()->GetTileId(mouse_position);
	}

public:
	ControlState(GameWorldForInput* _world) : world(_world) {}
	virtual void MouseHover(Vector2 position) = 0;
	virtual void MouseClick(Vector2 position) = 0;
	virtual void MouseRelease(Vector2 position) = 0;
	virtual void Reset() = 0;
	void SetGameWorld(GameWorldForInput* _world) { world = _world; }
	InputStatus GetInputStatus() { return input; }
};

class NormalState : public ControlState {
public:
	NormalState(GameWorldForInput* _world): ControlState(_world){}

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
		input.ResetDrag();
	}
};

class BuildState : public ControlState {
private:
	void HighlightHoverdTile(Vector2 mouse_position) {
		int hovered_tile_id = GetTileIDIfMouseHoverTileMap(mouse_position);
		if (hovered_tile_id >= 0) {
			Tile hoverd_tile = world->GetTileMap()->GetTile(hovered_tile_id);
			input.is_area_highlighted = true;
			input.highlighted_area = hoverd_tile.GetPhysics().GetRect();
		}
		else {
			input.is_area_highlighted = false;
		}
	}
public:
	BuildState(GameWorldForInput* _world) : ControlState(_world) {}

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
		input.is_area_highlighted = false;
	}
};

class ControlContext {
private:
	ControlState* current_state;
	NormalState* normal_state;
	BuildState* build_state;

public:
	ControlContext(GameWorldForInput* world){
		normal_state = new NormalState(world);
		build_state = new BuildState(world);
		current_state = normal_state;
	}
	~ControlContext() {
		delete normal_state;
		delete build_state;
	}

	void SwitchToNormalState() {
		current_state->Reset();
		current_state = normal_state;
	}

	void SwitchToBulidState() {
		current_state->Reset();
		current_state = build_state;
	}

	void MouseHover(Vector2 mouse_position) {
		current_state->MouseHover(mouse_position);
	}

	void MouseClick(Vector2 mouse_position) {
		current_state->MouseClick(mouse_position);
	}

	void MouseRelease(Vector2 mouse_position) {
		current_state->MouseRelease(mouse_position);
	}

	InputStatus GetInputStatus() {
		return current_state->GetInputStatus();
	}
};
