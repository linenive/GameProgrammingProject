extends CanvasLayer

export (NodePath) var setting_menu_btn

# Called when the node enters the scene tree for the first time.
func _ready():
	pass
	#add_items()

func add_items():
	$HBoxContainer/MenuButton4.get_popup().add_item("설정")
	$HBoxContainer/MenuButton4.get_popup().add_item("게임 저장")
	$HBoxContainer/MenuButton4.get_popup().add_item("게임 종료")
