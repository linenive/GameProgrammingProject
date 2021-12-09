extends GridContainer

var inventory_slot_scene

# Called when the node enters the scene tree for the first time.
func _ready():
	inventory_slot_scene = load("res://Scene/InventorySlot.tscn")

func init_inventory(inventory_info_start_index, info : Array):
	delete_all_inventory_slot()
	
	var inventory_size = 0
	
	var inventory_slot_instance
	
	for i in range(inventory_info_start_index, len(info)):
		inventory_slot_instance = inventory_slot_scene.instance()
		inventory_slot_instance.init_inventory_slot(info[i])
		self.add_child(inventory_slot_instance)
		inventory_size += 1
	
	self.columns = pow(inventory_size, 0.5)

func delete_all_inventory_slot():
	for slot in self.get_children():
		self.remove_child(slot)
