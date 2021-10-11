extends Node

var world_manager
var tile_scene
var character_scene

func _ready():
	world_manager = get_node("/root/Main/WorldManager")
	tile_scene = load("res://Scene/Tile.tscn")
	character_scene = load("res://Scene/Character.tscn")
	
	tile_map_create()
	
func tile_map_create():
	var tile_size = world_manager.GetTileNumber()
	
	for i in tile_size:
		var node = tile_scene.instance()
		
		var transform =	world_manager.GetTileTransform(i)
		node.transform = transform
		$Tile.add_child(node)

func new_character(x, y):
	var character_instance = character_scene.instance()
	var transform2 = Transform2D(0, Vector2(x, y));
	world_manager.TestNewCharacter(transform2)
	character_instance.transform = transform2
	$Character.add_child(character_instance)

func _process(delta):
	var character_num = world_manager.GetCharacterNumber()
	for i in character_num:
		var transform3 = world_manager.GetCharacterTransform(i)
		$Character.get_child(i).transform = transform3

func _on_Button_pressed():
	var x = get_node("/root/Main/x").get_line(0)
	var y = get_node("/root/Main/y").get_line(0)
	new_character(float(x), float(y))
