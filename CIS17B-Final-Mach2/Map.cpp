#include "Map.h"
#include <fstream>
#include <iostream>
#include "BoxCollider.h"

Map::Map(std::string tileSetPath, std::string mapFilePath, int sizeX, int sizeY)
{
	mTileSetPath = tileSetPath;
	mMapFilePath = mapFilePath;
	mSizeX = sizeX;
	mSizeY = sizeY;
}

Map::~Map()
{
	mMapTiles.clear();
	mMapTiles.~vector();
	// std::vector<Texture*>().swap(mMapTiles); // instant de-allocation!
	for (Collider* c : mMapColliders)
	{
		delete c;
		c = NULL;
	}
	//superfulous?
	mMapColliders.clear();
	mMapColliders.~vector();
}

// Load the .map tiles:
void Map::LoadMap()
{
	char c;
	std::fstream mapFile;
	mapFile.open(mMapFilePath);
	if (!mapFile) { std::cout << "Failed to open file\n"; }

	int srcX, srcY;

	// these loops parse the .map file:
	for (int y = 0; y < mSizeY; y++)
	{
		for (int x = 0; x < mSizeX; x++)
		{
			mapFile.get(c);
			//std::cout << c << " "; // debug
			srcY = atoi(&c)*TILE_SIZE; // atoi := character string-to-int
			mapFile.get(c); // debug
			//std::cout << c << std::endl;
			srcX = atoi(&c)*TILE_SIZE;
			AddTile(srcX, srcY, x * (TILE_SIZE), y * (TILE_SIZE));
			mapFile.ignore(); //skip the comma
			// std::cout << srcX << " " << srcY << std::endl;
		}
	}
	mapFile.close();
}


/*
TODO: This can still be refactored because right now we need to pass a specific Map object,
to run this function, but the tileset (.png) associated with it is worthless there; we only
need it here to initialize "scaledSize", which should be set for every map in the game.
*/

// TODO

void Map::LoadColliders(std::string colFilePath)
{
	char c;
	std::fstream mapFile;
	mapFile.open(colFilePath);
	int srcX, srcY;
	for (int y = 0; y < mSizeY; y++)
	{
		for (int x = 0; x < mSizeX; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				BoxCollider* bc = new BoxCollider(Vector2(28.0f, 28.0f));
				AddCollider(bc, Vector2(x*TILE_SIZE, y*TILE_SIZE));
				mMapColliders.push_back(std::move(bc));
				//BoxCollider bc = BoxCollider(Vector2(TILE_SIZE, TILE_SIZE));
				//AddCollider(&bc);
				//mColliders.push_back(bc);
				//mColliders.back().Parent(this);
				//mColliders.back().Pos(Vector2(x*TILE_SIZE, y*TILE_SIZE));
				/*
				auto& tileCollider(manager.addEntity());
				tileCollider.addComponent<ColliderComponent>("terrainCollider", x * scaledSize, y * scaledSize, scaledSize, scaledSize);
				tileCollider.addGroup(Game::groupColliders);
				*/
			}
			mapFile.ignore();
		}
	}
	mapFile.close();
}


void Map::AddTile(int srcX, int srcY, int posX, int posY)
{
	// std::cout << srcX << " " << srcY << std::endl;

	Texture texture = Texture(mTileSetPath, srcX, srcY, TILE_SIZE, TILE_SIZE);
	mMapTiles.push_back(texture);
	mMapTiles.back().Parent(this);
	mMapTiles.back().Pos(Vector2(posX, posY));
	/*
	mMapTiles.push_back(new Texture(mTileSetPath, srcX, srcY, TILE_SIZE, TILE_SIZE));
	mMapTiles.back()->Parent(this);
	mMapTiles.back()->Pos(Vector2(posX, posY));
	*/
}

void Map::Render()
{
	for (Texture t : mMapTiles)
		t.Render();
	/*
	for (Collider c : mColliders)
		c.PhysicsEntity::Render();
	*/
	for (Collider* c : mMapColliders)
		c->Render();
}