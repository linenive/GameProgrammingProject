extends Node

var texture_db

var building_data_array : Array
var BUILDING_COUNT = 2

var furniture_data_array : Array
var FURNITURE_COUNT = 8

# Called when the node enters the scene tree for the first time.
func _ready():
	texture_db = get_node("/root/Main/TextureDB")
	set_furniture_data_array()
	set_building_data_array()

func get_furniture_data_array():
	return furniture_data_array

func set_furniture_data_array():
	for i in range(FURNITURE_COUNT):
		furniture_data_array.append(["furniture"+str(i+1), texture_db.structure_texture[i], i])

func get_building_data_array():
	return building_data_array

func set_building_data_array():
	for i in range(BUILDING_COUNT):
		building_data_array.append(["building"+str(i+1), texture_db.structure_texture[i], i])
