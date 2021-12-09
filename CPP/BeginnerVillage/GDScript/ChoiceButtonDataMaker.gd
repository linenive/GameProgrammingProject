extends Node

var texture_db

var building_name_arrray = ["작은 집", "커다란 집", "쓰리룸 집", "상점", "투룸 상점1", "투룸 상점2"]
var building_data_array : Array
var BUILDING_COUNT = 6

var furniture_name_arrray = ["싱글 베드", "더블 베드", "작은 상자", "싱크대", "화병", "카운터", "테이블", "의자"]
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
		furniture_data_array.append([furniture_name_arrray[i], texture_db.structure_texture[i], i])

func get_building_data_array():
	return building_data_array

func set_building_data_array():
	for i in range(BUILDING_COUNT):
		building_data_array.append([building_name_arrray[i], texture_db.building_blueprint_texture[i], i])
