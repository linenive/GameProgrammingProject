extends WindowDialog

var uicontrol
var world_manager

var target_object_id = 0

var target_node
var target_type

# Called when the node enters the scene tree for the first time.
func _ready():
	uicontrol = get_node("/root/Main/UIControl")
	world_manager = get_node("/root/Main/WorldManager")

func show_popup(node, type, window_position:Vector2):
	if target_object_id == 0:
		setting_popup(node, type)
	
	set_position(window_position)	
	window_title = convert_type_to_window_title(type)
	
	var btn = get_close_button()
	btn.connect("pressed", self, "close_button_pressed")
	
	show_info_by_type(node, type)
	
	show()

func show_info_by_type(node, type):
	if(type == "Character"):
		window_setting_character_info(node)

func _process(delta):
	if(is_visible_in_tree()):
		show_info_by_type(target_node, target_type)

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

func convert_type_to_window_title(type):
	var window_title = "Info Title"
	
	if type == "Character":
		window_title = "Character Info"
	elif type == "Tile":
		window_title = "Tile Info"
		
	return window_title

func window_setting_character_info(node_character):
	set_title("Character Info")	
	
	var character = node_character as Sprite
	var character_info = get_character_info(node_character)
	
	$title.text = character_info["name"]
	$content.text = str(node_character.get_position())
	$CharacterSprite.texture = character.texture
	
	$InventoryTitle.text = "Inventory"
	$ItemName.text = character_info["item1"][0]
	$itemType.text = character_info["item1"][1]

func get_character_info(node):
	var characters_size = world_manager.GetCharacterNumber();
	var inventory_size : int
	var item_info_array : Array
	
	var character_position = node.get_position()
	var character_info = {}
	
	for i in characters_size:
		if character_position == world_manager.GetCharacterTransform(i).origin:
			character_info["name"] = world_manager.GetCharacterName(i)
			inventory_size = world_manager.GetCharacterInventorySize(i)
			
			for j in inventory_size:
				item_info_array = world_manager.GetCharacterItem(i, j);
				character_info["item" + str(j+1)] = item_info_array
	
	return character_info
