#pragma once
#include "testProperty.h"
#include "Base.h"
#include <Node.hpp>

class PathfindingManager : public Node {

	GODOT_CLASS(PathfindingManager, Node);

private:
	shared_ptr <JPSCollision> spCollision = std::make_shared<JPSCollision>();

public:
	static void _register_methods();

	int linktest = 3;
	list<JPSCoord> ResultNodes;
	PoolVector2Array ResultPaths;

	void _init();
	void _ready();
	void InitMap(Int32 width, Int32 height);
	void UpdateMap(Int32 gridWidth, Int32 gridHeight);
	void ScanningCollision(Int32 halfWidth);

	PoolVector2Array GetPath();
	void Search(Int32 Sx, Int32 Sy, Int32 Ex, Int32 Ey);//, list<JPSCoord>& ResultNodes);
	int GetPathLength() { return ResultNodes.size(); }
};