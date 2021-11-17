extends Node

var world_manager
var tile_scene
var block_scene
var character_scene
var texture_db

func _ready():	
	world_manager = get_node("/root/Main/WorldManager")
	texture_db = get_node("/root/Main/TextureDB")
	tile_scene = load("res://Scene/Tile.tscn")
	block_scene = load("res://Scene/Block.tscn")
	character_scene = load("res://Scene/Character.tscn")
	
	create_surface()

func create_surface():
	var tile_size = world_manager.GetTileNumber()
	
	for i in tile_size:
		var surface_node = tile_scene.instance()
		var transform =	world_manager.GetSurfaceTransform(i)
		surface_node.transform = transform
		surface_node.texture = tile_image_changer(world_manager.GetSurfaceType(i))
		$Tile.add_child(surface_node)
		create_blocks(i, transform)

func create_blocks(tile_id, transform):
	var block_types = world_manager.GetBlockTypes(tile_id)
	for bt in block_types:
		var block_node = block_scene.instance()
		block_node.transform = transform
		block_node.texture = texture_db.block_texture[bt]
		$Block.add_child(block_node)

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
