extends PanelContainer

func init_inventory_slot(item_info):
	if len(item_info) !=  0:
		$VBoxContainer/item_name_label.visible = true		
		$VBoxContainer/item_name_label.text = item_info[0]
		
		$VBoxContainer/item_count_label.visible = true		
		$VBoxContainer/item_count_label.text = "count : " + str(item_info[3])
	else:
		$VBoxContainer/item_name_label.visible = false
		$VBoxContainer/item_count_label.visible = false
