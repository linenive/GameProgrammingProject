extends Node

var character_texture = []
var block_texture = []
var structure_texture = []

# To-do: load db. not hard coding.
func load_db():
	character_texture.append(load("res://Image/DefaultCharacter1.png"))
	character_texture.append(load("res://Image/DefaultCharacter2.png"))
	
	block_texture.append(load("res://Image/block_door.png"))
	block_texture.append(load("res://Image/block_wall.png"))
	block_texture.append(load("res://Image/block_door.png"))
	block_texture.append(load("res://Image/block_floor.png"))
	
	structure_texture.append(load("res://Image/furniture_1.png"))
	structure_texture.append(load("res://Image/furniture_2.png"))
	structure_texture.append(load("res://Image/furniture_3.png"))
	structure_texture.append(load("res://Image/furniture_4.png"))
	structure_texture.append(load("res://Image/furniture_5.png"))
	structure_texture.append(load("res://Image/furniture_6.png"))
	structure_texture.append(load("res://Image/furniture_7.png"))
	structure_texture.append(load("res://Image/furniture_8.png"))

func _ready():
	load_db()
