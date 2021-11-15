extends ConfirmationDialog

var village_Info_UI

func _ready():
	village_Info_UI = get_node("/root/Main/UIControl/HUD/VillageInfoUI")
	
	get_ok().connect("pressed", self, "ok_btn_pressed")
	get_cancel().connect("pressed", self, "cancel_btn_pressed")

func init_confirmation_dialog(title, direction, hint, ok_btn_text="Yes", cancel_btn_text="No"):
	set_title(title)
	$VBoxContainer/Direction.text = direction
	$VBoxContainer/LineEdit.text = hint
	
	get_ok().text = ok_btn_text
	get_cancel().text = cancel_btn_text
	
	popup_centered()

func ok_btn_pressed():
	village_Info_UI.set_village_name($VBoxContainer/LineEdit.text)

func cancel_btn_pressed():
	pass
