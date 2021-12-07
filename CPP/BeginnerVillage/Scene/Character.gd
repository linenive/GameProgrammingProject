extends Sprite

var uicontrol
var godot_input

var character_id : int
var character_path

# Called when the node enters the scene tree for the first time.
func _ready():
	uicontrol = get_node("/root/Main/UIControl")
	godot_input = get_node("/root/Main/GodotInput")

func init_character(character_id):
	self.character_id = character_id

func get_id():
	return character_id
