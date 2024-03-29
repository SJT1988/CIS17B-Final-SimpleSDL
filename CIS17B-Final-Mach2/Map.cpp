#include "Map.h"
#include <fstream>
#include <iostream>
#include "BoxCollider.h"
//#include <regex>

Map::Map(std::string tileSetPath, std::string mapFilePath, int sizeX, int sizeY, int mapIndex)
{
	mTileSetPath = tileSetPath;
	mMapFilePath = mapFilePath;
	mSizeX = sizeX;
	mSizeY = sizeY;
	mMapIndex = mapIndex;
}

Map::~Map()
{
	for (Texture t : mMapTiles)
	{
		t.~Texture();
	}
	mMapTiles.clear();
	mMapTiles.~vector();
	// std::vector<Texture*>().swap(mMapTiles); // instant de-allocation!
	for (Collider* c : mMapColliders)
	{
		delete c;
		c = NULL;
	}
	//superfulous?
	//mMapColliders.clear();
	//mMapColliders.~vector();



	for (Texture* t : mColliders1)
	{
		delete t;
		t = NULL;
	}
	mColliders1.clear();
	mColliders1.~vector();
	for (Texture* t : mColliders2)
	{
		delete t;
		t = NULL;
	}
	mColliders2.clear();
	mColliders2.~vector();
	for (Texture* t : mColliders3)
	{
		delete t;
		t = NULL;
	}
	mColliders3.clear();
	mColliders3.~vector();
	
	delete mExit;
	mExit = NULL;
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


void Map::CreateColliders(std::string colFilePath)
{
	std::cout << colFilePath << std::endl;
	char c;
	std::fstream mapFile;
	mapFile.open(colFilePath);
	//int srcX, srcY;
	for (int y = 0; y < mSizeY; y++)
	{
		for (int x = 0; x < mSizeX; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				mColliders1.push_back(new Texture("collider.png"));
				mColliders1.back()->Parent(this);
				mColliders1.back()->Pos(Vector2(x * (TILE_SIZE), y * (TILE_SIZE)));
			}
			else if (c == '2')
			{
				mColliders2.push_back(new Texture("collider2.png"));
				mColliders2.back()->Parent(this);
				mColliders2.back()->Pos(Vector2(x * (TILE_SIZE), y * (TILE_SIZE)));
				mColliders2.back()->Scale(Vector2(0.75f, 0.75f));
			}
			else if (c == '3')
			{
				mColliders3.push_back(new Texture("collider3.png"));
				mColliders3.back()->Parent(this);
				mColliders3.back()->Pos(Vector2(x * (TILE_SIZE), y * (TILE_SIZE)));
				mColliders3.back()->Scale(Vector2(0.75f, 0.75f));
			}
			else if (c == '4')
			{
				mExit = new Texture("exit.png");
				mExit->Parent(this);
				mExit->Pos(Vector2(x * (TILE_SIZE), y * (TILE_SIZE)));
			}
			mapFile.ignore();
		}
	}
	mapFile.close();
}


// TODO
/*
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
				
				//auto& tileCollider(manager.addEntity());
				//tileCollider.addComponent<ColliderComponent>("terrainCollider", x * scaledSize, y * scaledSize, scaledSize, scaledSize);
				//tileCollider.addGroup(Game::groupColliders);
				
			}
			mapFile.ignore();
		}
	}
	mapFile.close();
}
*/

void Map::AddTile(int srcX, int srcY, int posX, int posY)
{
	// std::cout << srcX << " " << srcY << std::endl;

	Texture texture = Texture(mTileSetPath, srcX, srcY, TILE_SIZE, TILE_SIZE);

	SDL_SetTextureColorMod(texture.mTex, 255, 255, 255);
	// This part "darkens" the map each level:
	// string ends in "map##.map"
	/*
	if (std::regex_match(mMapFilePath, std::regex(".*(map)[0-9]{2}(\.)(map)$")) && mMapIndex != 0)
	{
		std::cout << "darken" << std::endl;
		int amount = 255 * (1 - mMapIndex * 0.05f);
		SDL_SetTextureColorMod(texture.mTex, amount, amount, amount);
	}
	*/
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
	/*
	for (Collider* c : mMapColliders)
		c->Render();
	*/
	for (Texture* t : mColliders1)
	{
		t->Render();
	}
	for (Texture* t : mColliders2)
	{
		t->Render();
	}
	for (Texture* t : mColliders3)
	{
		t->Render();
	}
	if (mExit)
		mExit->Render();
}