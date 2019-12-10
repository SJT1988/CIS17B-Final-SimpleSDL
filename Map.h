#pragma once
#include <string>
#include "Texture.h"
#include <vector>
#include "Collider.h"

using namespace QuickSDL;

class Map : public GameEntity
{
private:

	std::vector<Texture> mMapTiles;
	std::string mTileSetPath;
	int mMapIndex;
	
public:

	const int TILE_SIZE = 32;
	int mSizeX;
	int mSizeY;
	std::string mMapFilePath;

	// these are accessed in PlayScreen.cpp to test collisions.
	std::vector<Collider*> mColliders1;
	std::vector<Collider*> mColliders2;
	std::vector<Collider*> mColliders3;
	Collider* mExit; //4

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