#pragma once
#include <string>
#include "Texture.h"
#include <vector>
#include "PhysicsEntity.h"

using namespace QuickSDL;

class Map : public PhysicsEntity
{
private:

	std::vector<Texture> mMapTiles;
	std::vector<Collider*> mMapColliders;
	std::string mTileSetPath;
	
	
public:

	const int TILE_SIZE = 32;
	int mSizeX;
	int mSizeY;
	std::string mMapFilePath;

public:
	Map(std::string tileSetPath, std::string mapFilePath, int sizeX, int sizeY);
	~Map();

	void LoadMap();
	// void LoadMap(std::string path, int sizeX, int sizeY);
	
	void LoadColliders(std::string colFilePath);
	
	void Render();

private:

	void AddTile(int srcX, int srcY, int posX, int posY);
	
};