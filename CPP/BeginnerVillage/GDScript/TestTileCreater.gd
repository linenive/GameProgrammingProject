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
	
	CreateTileMap()

func CreateSurface(tile_coord, transform):
	var surface_node = tile_scene.instance()
	surface_node.transform = transform
	surface_node.texture = tile_image_changer(world_manager.GetSurfaceType(tile_coord))
	$Tile.add_child(surface_node)

func CreateTileMap():
	var tile_size_x = world_manager.GetTileSizeX()
	var tile_size_y = world_manager.GetTileSizeY()
	
	for j in range(tile_size_y):
		for i in range(tile_size_x):
			var transform = world_manager.GetSurfaceTransform(Vector2(i, j))
			CreateSurface(Vector2(i, j), transform)
			CreateBlocks(Vector2(i, j), transform)

func CreateBlocks(tile_coord, transform):
	var block_types = world_manager.GetBlockTypes(tile_coord)
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

# 위가 임시고 이게 정식 함수
func create_character(id):
	var character_instance = character_scene.instance()
	var transform2 = world_manager.GetCharacterTransform(id)
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

func _on_InputManager_build_building(ID):
	CreateBuildingNodes(ID)

func CreateBuildingNodes(building_id):
	for n in $Block.get_children():
		$Block.remove_child(n)
		n.queue_free()
	
	var tile_size_x = world_manager.GetTileSizeX()
	var tile_size_y = world_manager.GetTileSizeY()
	
	for j in range(tile_size_y):
		for i in range(tile_size_x):
			var coordinate = world_manager.GetSurfaceTransform(Vector2(i, j))
			CreateBlocks(Vector2(i, j), coordinate)

func _on_Main_create_character(ID):
	create_character(ID)
