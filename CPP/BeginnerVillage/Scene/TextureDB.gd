extends Node

var character_texture = []
var block_texture = []
var structure_texture = []
var building_blueprint_texture = []

# To-do: load db. not hard coding.
func load_db():
	character_texture.append(load("res://Image/character_1.png"))
	character_texture.append(load("res://Image/character_2.png"))
	character_texture.append(load("res://Image/character_3.png"))
	character_texture.append(load("res://Image/character_4.png"))
	
	block_texture.append(load("res://Image/block_door.png"))
	block_texture.append(load("res://Image/block_wall.png"))
	block_texture.append(load("res://Image/block_door.png"))
	block_texture.append(load("res://Image/block_floor.png"))
	block_texture.append(load("res://Image/block_shopsign.png"))
	
	structure_texture.append(load("res://Image/furniture_1.png"))
	structure_texture.append(load("res://Image/furniture_2.png"))
	structure_texture.append(load("res://Image/furniture_3.png"))
	structure_texture.append(load("res://Image/furniture_4.png"))
	structure_texture.append(load("res://Image/furniture_5.png"))
	structure_texture.append(load("res://Image/furniture_6.png"))
	structure_texture.append(load("res://Image/furniture_7.png"))
	structure_texture.append(load("res://Image/furniture_8.png"))
	structure_texture.append(load("res://Image/tree_1.png"))
	
	building_blueprint_texture.append(load("res://Image/building_blueprint/small_house.png"))
	building_blueprint_texture.append(load("res://Image/building_blueprint/large_house.png"))
	building_blueprint_texture.append(load("res://Image/building_blueprint/three_room_house.png"))
	building_blueprint_texture.append(load("res://Image/building_blueprint/shop.png"))
	building_blueprint_texture.append(load("res://Image/building_blueprint/two_room_shop_1.png"))
	building_blueprint_texture.append(load("res://Image/building_blueprint/two_room_shop_2.png"))

func _ready():
	load_db()
