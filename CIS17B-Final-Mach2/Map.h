#pragma once
#include <string>
#include "Texture.h"
#include <vector>

using namespace QuickSDL;

class Map : public GameEntity
{
private:

	std::vector<Texture> mMapTiles;
	//std::vector<Texture*> mMapTiles;	
	std::string mTileSetPath;
	std::string mMapFilePath;
	
public:

	const int TILE_SIZE = 32;
	int mSizeX;
	int mSizeY;

public:
	Map(std::string tileSetPath, std::string mapFilePath, int sizeX, int sizeY);
	~Map();

	void LoadMap();
	// void LoadMap(std::string path, int sizeX, int sizeY);
	
	// void LoadColliders(std::string path, int sizeX, int sizeY);
	
	void Render();

private:

	void AddTile(int srcX, int srcY, int posX, int posY);
	
};