extends Sprite
var structure_id : int

# Called when the node enters the scene tree for the first time.
func _ready():
	pass

func init_id(id):
	self.structure_id = id

func get_id():
	return structure_id
