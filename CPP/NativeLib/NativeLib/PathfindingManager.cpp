#include "PathfindingManager.h"
#include "Common.h"

void PathfindingManager::_register_methods() {
	register_method("_ready", &PathfindingManager::_ready);
	register_method("InitMap", &PathfindingManager::InitMap);
	register_method("GetPathLength", &PathfindingManager::GetPathLength);

	register_property<PathfindingManager,PoolVector2Array>("ResultPaths", &PathfindingManager::ResultPaths, PoolVector2Array());
	register_property<PathfindingManager, int>("linktest", &PathfindingManager::linktest, 7);
}

void PathfindingManager::_init() {

}
void PathfindingManager::_ready() {
	linktest+=10;

}
void PathfindingManager::InitMap(Int32 width, Int32 height){

	UpdateMap(width, height);
	Search(1, 1, width-2, 2);
	ResultPaths = GetPath();
	linktest += 10;
}

void PathfindingManager::UpdateMap(Int32 gridWidth, Int32 gridHeight){

	spCollision->Create(gridWidth, gridHeight);
	ScanningCollision(gridWidth/2);
}

void PathfindingManager::ScanningCollision(Int32 halfWidth){
	//세로로 반절쯤 막는 벽
	for (Int32 i = 0; i < halfWidth; i++)
	{
		spCollision->SetAt(halfWidth, i);
	}
}

PoolVector2Array PathfindingManager::GetPath() {
	PoolVector2Array pathlist;
	list<JPSCoord>::iterator it;

	Int32 x, y;
	for (it = ResultNodes.begin(); it != ResultNodes.end(); it++) {
		x = (*it).m_x;
		y = (*it).m_y;
		pathlist.append(Vector2(x, y));
	}
	return pathlist;
}

void PathfindingManager::Search(Int32 Sx, Int32 Sy, Int32 Ex, Int32 Ey){
	
	JPSPath	jps;
	jps.Init(spCollision);
	jps.Search(Sx, Sy, Ex, Ey, ResultNodes);
}
