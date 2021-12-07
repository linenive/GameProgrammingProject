extends WindowDialog

var uicontrol
var static_unit_manager

var target_node_id = 0

var target_node
var target_type

# Called when the node enters the scene tree for the first time.
func _ready():
	uicontrol = get_node("/root/Main/UIControl")

func show_popup(node, type, info, window_position:Vector2):
	if target_node_id == 0:
		setting_popup(node, type)
	
	set_position(window_position)	
	
	var btn = get_close_button()
	btn.connect("pressed", self, "close_button_pressed")
	
	show_info_by_type(info)
	
	show()

func show_info_by_type(info):
	$CharacterInfo.visible = false
	$ItemInfo.visible = false
	$BuildingInfo.visible = false
	
	#$BuildingInfo.visible = true
	#$BuildingInfo.window_setting_building_info(target_node, info)
	
	if(target_type == "Character"):
		$CharacterInfo.visible = true
		$CharacterInfo.window_setting_character_info(target_node, info)
	elif(target_type == "Building"):
		$BuildingInfo.visible = true
		$BuildingInfo.window_setting_building_info(target_node, info)

func _process(delta):
	if uicontrol.is_used_popup(self):
		if target_type == "Character":
			show_info_by_type(uicontrol.get_character_info(target_node))

func init_popup():
	target_node_id = 0
	target_node = null
	target_type = ""

func setting_popup(node, type):
	target_node_id = node.get_instance_id()
	target_node = node
	target_type = type

func close_button_pressed():
	init_popup()
	uicontrol.close_info_popup(self)

func _gui_input(event):
	if event is InputEventMouseButton and event.pressed and event.button_index == BUTTON_LEFT:
		uicontrol.set_ui_top(self)

func get_target_node():
	return target_node

func get_target_node_id():
	return target_node_id

func set_target_node_id(node_id):
	target_node_id = node_id
