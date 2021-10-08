extends Node


func _ready():
	var tile_scene = load("res://Scene/Tile.tscn")
	
	
	var tile_size = get_node("/root/Main/WorldManager").GetTileSize()
	
	for i in tile_size:
		var node = tile_scene.instance()
		
		var transform =	get_node("/root/Main/WorldManager").GetTileTransform(i)
		node.transform = transform
		add_child(node)



#func _process(delta):
#	pass
