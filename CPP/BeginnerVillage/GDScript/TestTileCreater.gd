extends Node

var world_manager
var tile_scene
var block_scene
var structure_scene
var character_scene
var texture_db
var static_unit_manager

func _ready():	
	world_manager = get_node("/root/Main/WorldManager")
	texture_db = get_node("/root/Main/TextureDB")
	tile_scene = load("res://Scene/Tile.tscn")
	block_scene = load("res://Scene/Block.tscn")
	structure_scene = load("res://Scene/Object/Structure.tscn")
	character_scene = load("res://Scene/Object/Character.tscn")
	static_unit_manager = get_node("/root/Main/StaticUnitManager")
	
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
		if bt>=texture_db.block_texture.size():
			continue;
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

func create_man_character(id):
	var character_instance = character_scene.instance()
	var transform2 = world_manager.GetCharacterTransform(id)
	character_instance.transform = transform2
	character_instance.texture = texture_db.character_texture[0]
	$Character.add_child(character_instance)
	
	character_instance.init_character(id)

func create_woman_character(id):
	var character_instance = character_scene.instance()
	var transform2 = world_manager.GetCharacterTransform(id)
	character_instance.transform = transform2
	character_instance.texture = texture_db.character_texture[1]
	$Character.add_child(character_instance)
	
	character_instance.init_character(id)

func delete_character(id):
	for c in $Character.get_children():
		if c.character_id == id:
			$Character.remove_child(c)
			return

func _process(delta):
	for c in $Character.get_children():
		var transform3 = world_manager.GetCharacterTransform(c.character_id)
		if transform3.origin.x == -1:
			print("[TestTileCreater]There's no character transform data. id:" + String( c.character_id))
			continue
		c.transform = transform3

func _on_InputManager_build_building(ID):
	create_building_nodes(ID)

func _on_InputManager_install_structure(ID):
	create_structure(ID)

func create_building_nodes(building_id):
	for n in $Block.get_children():
		$Block.remove_child(n)
		n.queue_free()
	
	var tile_size_x = world_manager.GetTileSizeX()
	var tile_size_y = world_manager.GetTileSizeY()
	
	for j in range(tile_size_y):
		for i in range(tile_size_x):
			var coordinate = world_manager.GetSurfaceTransform(Vector2(i, j))
			CreateBlocks(Vector2(i, j), coordinate)

func create_structure(structure_id):
	var structure_instance = structure_scene.instance()
	var structure_type = static_unit_manager.GetStructureType(structure_id)
	var position = static_unit_manager.GetStructurePosition(structure_id)
	structure_instance.transform.origin = position
	structure_instance.texture = texture_db.structure_texture[structure_type]
	$Structure.add_child(structure_instance)

func _on_Main_create_character(ID):
	var gender = world_manager.GetCharacterGender(ID)
	if(gender == "Man"):
		create_man_character(ID)
	elif(gender == "Woman"):
		create_woman_character(ID)
	
func _on_Main_delete_character(ID):
	delete_character(ID)

func _on_Button_pressed():
	var character_id = get_node("/root/Main/UIControl/HUD/x").get_line(0)
	#var building_id = get_node("/root/Main/UIControl/HUD/y").get_line(0)
	static_unit_manager.RecruitGuestAsResident(character_id)
