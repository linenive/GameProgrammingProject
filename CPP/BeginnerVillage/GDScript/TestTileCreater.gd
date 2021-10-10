extends Node


func _ready():
	var tile_scene = load("res://Scene/Tile.tscn")
	var character_scene = load("res://Scene/Character.tscn")
	
	var tile_size = get_node("/root/Main/WorldManager").GetTileNumber()
	
	for i in tile_size:
		var node = tile_scene.instance()
		
		var transform =	get_node("/root/Main/WorldManager").GetTileTransform(i)
		node.transform = transform
		add_child(node)
		
	var transform2 = Transform2D(0, Vector2(400, 300));
	get_node("/root/Main/WorldManager").TestNewCharacter(transform2)
	
	get_node("/root/Main/WorldManager").SetNumber()
	
	#for i in get_node("/root/Main/WorldManager").GetCharacterNumber():
	#	var character_instance = character_scene.instance()
	#	var transform3 = get_node("/root/Main/WorldManager").GetCharacterTransform(0)
	#	character_instance.transform = transform3
	#	add_child(character_instance)

func _process(delta):
	get_node("/root/Main/HeyTest").text = String(get_node("/root/Main/WorldManager").GetCharacterNumber())
	
