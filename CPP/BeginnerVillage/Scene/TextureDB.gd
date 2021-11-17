extends Node

var block_texture = []

# To-do: load db. not hard coding.
func load_db():
	block_texture.append(load("res://Image/block_door.png"))
	block_texture.append(load("res://Image/block_wall.png"))
	block_texture.append(load("res://Image/block_door.png"))
	block_texture.append(load("res://Image/block_floor.png"))

func _ready():
	load_db()
