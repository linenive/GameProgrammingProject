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
		node.texture = tile_image_changer(world_manager.GetTileType(i))
		$Tile.add_child(node)

func tile_image_changer(tile_type_id):
	var texture;
	if tile_type_id==1:
		texture = load("res://Image/tile_earth.png")
	elif tile_type_id==3:
		texture = load("res://Image/tile_river.png")
	elif tile_type_id==4:
		texture = load("res://Image/tile_ocean.png")
	else:
		texture = load("res://Image/tile_default.png")
	return texture;

func new_character(x, y):
	var character_instance = character_scene.instance()
	var transform2 = Transform2D(0, Vector2(x, y));
	world_manager.TestNewCharacter(transform2)
	character_instance.transform = transform2
	$Character.add_child(character_instance)
	
	character_instance.init_character(world_manager.GetCharacterNumber()-1)

func _process(delta):
	var character_num = world_manager.GetCharacterNumber()
	for i in character_num:
		var transform3 = world_manager.GetCharacterTransform(i)
		$Character.get_child(i).transform = transform3

func _on_Button_pressed():
	var x = get_node("/root/Main/UIControl/HUD/x").get_line(0)
	var y = get_node("/root/Main/UIControl/HUD/y").get_line(0)
	new_character(float(x), float(y))
