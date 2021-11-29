extends WindowDialog

var uicontrol
var world_manager

var target_object_id = 0

var target_node
var target_type

var guest_info_ui_array : Array
var resident_info_ui_array : Array

# Called when the node enters the scene tree for the first time.
func _ready():
	uicontrol = get_node("/root/Main/UIControl")
	
	guest_info_ui_array.append($CharacterInfo/GuestInfo)
	guest_info_ui_array.append($CharacterInfo/HBoxContainer/GuestInfo)
	
	resident_info_ui_array.append($CharacterInfo/ResidentInfo)
	resident_info_ui_array.append($CharacterInfo/HBoxContainer/ResidentInfo)

func show_popup(node, type, info, window_position:Vector2):
	if target_object_id == 0:
		setting_popup(node, type)
	
	set_position(window_position)	
	
	var btn = get_close_button()
	btn.connect("pressed", self, "close_button_pressed")
	
	show_info_by_type(node, type, info)
	
	show()

func show_info_by_type(node, type, info):
	if(type == "Character"):
		window_setting_character_info(node, info)
	#elif():
		

func _process(delta):
	if(is_visible_in_tree()):
		show_info_by_type(target_node, target_type, uicontrol.get_character_info(target_node))
	pass

func init_popup():
	target_object_id = 0
	target_node = null
	target_type = ""

func setting_popup(node, type):
	target_object_id = node.get_instance_id()
	target_node = node
	target_type = type

func close_button_pressed():
	init_popup()
	uicontrol.close_info_popup(self)

func get_target_object_id():
	return target_object_id

func set_target_object_id(oid):
	target_object_id = oid

func _gui_input(event):
	if event is InputEventMouseButton and event.pressed and event.button_index == BUTTON_LEFT:
		uicontrol.set_ui_top(self)

func position_to_string(position):
	var x = round(position.x)
	var y = round(position.y)
	
	return "(" + str(x) + ", " + str(y) + ")"

func window_setting_character_info(node_character, info):
	$ItemInfo.visible = false
	$CharacterInfo.visible = true	
	
	var character = node_character as Sprite
	
	$CharacterInfo/VBoxContainer/HBoxContainer/content_character_first_name.text = info["first_name"]
	$CharacterInfo/VBoxContainer/HBoxContainer/content_character_last_name.text = info["last_name"]
	$CharacterInfo/VBoxContainer/HBoxContainer4/content_character_gender.text = info["gender"]
	$CharacterInfo/VBoxContainer/HBoxContainer3/content_character_position.text = position_to_string(node_character.get_position())
	$CharacterInfo/character_texture.texture = character.texture
	
	$CharacterInfo/title_inventory.text = "Inventory"
	$CharacterInfo/InventorySlot/VBoxContainer/content_item_name.text = info["item1"][0]
	$CharacterInfo/InventorySlot/VBoxContainer/content_item_type.text = info["item1"][1]
	
	window_setting_guest_info()
	
	#if "guest 인지":
	#	window_setting_guest_info()
	#else:
	#	window_setting_resident_info()

func window_setting_guest_info():
	set_title("Guest Info")	
	$CharacterInfo/title_character_info.text = "Guest Info"
	
	for ui in guest_info_ui_array:
		ui.visible = true
	
	for ui in resident_info_ui_array:
		ui.visible = false

func window_setting_resident_info():
	set_title("Resident Info")	
	$CharacterInfo/title_character_info.text = "Resident Info"
	
	for ui in guest_info_ui_array:
		ui.visible = false
	
	for ui in resident_info_ui_array:
		ui.visible = true

func _on_track_btn_pressed():
	uicontrol.popup_ui_track_btn_pressed(target_node.get_position())
