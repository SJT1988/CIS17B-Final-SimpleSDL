#pragma once
#include <string>
#include "Texture.h"
#include <vector>
#include "PhysicsEntity.h"
#include "BoxCollider.h"


using namespace QuickSDL;

class Map : public PhysicsEntity
{
private:

	std::vector<Texture> mMapTiles;
	std::string mTileSetPath;
	int mMapIndex;

	//std::string mColliderPath;
	std::vector<BoxCollider*> mColliders1;
	std::vector<BoxCollider*> mColliders2;
	std::vector<BoxCollider*> mColliders3;
	BoxCollider* mExit; //4
	
	
public:

	const int TILE_SIZE = 32;
	int mSizeX;
	int mSizeY;
	std::string mMapFilePath;

public:
	Map(std::string tileSetPath, std::string mapFilePath, int sizeX, int sizeY, int mapIndex = 0);
	~Map();

	void LoadMap();
	// void LoadMap(std::string path, int sizeX, int sizeY);
	
	void CreateColliders(std::string colFilePath);
	//void LoadColliders(std::string colFilePath);
	
	void Render();

private:

	void AddTile(int srcX, int srcY, int posX, int posY);
	
};