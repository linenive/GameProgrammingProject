extends Node

var is_pressed
var is_paused

func _ready():
	is_pressed = false

#error, not used
func _on_GoTitle_pressed():
	if DetectButtonClicked():
		SetPanelPause(false)
		is_pressed = false
		var err = get_tree().change_scene("res://Scene/Title.tscn")
		if err == OK:
			pass
		elif err == ERR_CANT_CREATE:
			breakpoint
		elif err == ERR_CANT_OPEN:
			breakpoint

func _on_Exit_pressed():
	if DetectButtonClicked():
		get_tree().quit()

func _on_Close_pressed():
	if DetectButtonClicked():
		SetPanelPause(false)
		is_pressed = false
		
func DetectButtonClicked():
	if is_pressed == false:
		is_pressed = true
		return true
	return false
	
func SetPanelPause(active):
	$TitleCanvas/TitlePanel.visible = active
	$ButtonCanvas/Control.visible = active
	$ColorRect.visible = active
	get_tree().paused = active
	is_paused = active

