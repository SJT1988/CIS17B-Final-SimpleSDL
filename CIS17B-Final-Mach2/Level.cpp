#include "Level.h"

Level::Level(int level, HUD* hud, Player* player)
{
	mTimer = Timer::Instance();
	mHUD = hud;
	mHUD->SetCurrentScore(level);

	mLevel = level;
	mLevelStarted = false;
	mLabelTimer = 0.0f;
	/*
	mLevelLabel = new Texture("LEVEL", "forgotmybazookaathome.ttf", 24, { 64,64,255 });
	mLevelLabel->Parent(this);
	mLevelLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f - 13, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	mLevelNumber = new ScoreBoard({64, 64, 255 });
	mLevelNumber->Score(mLevel);
	mLevelNumber->Parent(this);
	mLevelNumber->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f + 123, Graphics::Instance()->SCREEN_HEIGHT*0.5f));
	*/
	mLevelLabelOnScreen = 0.0f;
	mLevelLabelOffScreen = 1.0f;

	mPlayer = player;

	// Map stuff
	/*
	mTileSetPath = "tileset.png";
	CreateMaps();
	for (Map* m : mMaps)
		m->Pos(Vector2((Graphics::Instance()->SCREEN_WIDTH - m->mSizeX * m->TILE_SIZE)*0.5f,
		(Graphics::Instance()->SCREEN_HEIGHT - m->mSizeY * m->TILE_SIZE)*0.5f));
	
	for (Map* fx : mFxMaps)
		fx->Pos(Vector2((Graphics::Instance()->SCREEN_WIDTH - fx->mSizeX * fx->TILE_SIZE)*0.5f,
		(Graphics::Instance()->SCREEN_HEIGHT - fx->mSizeY * fx->TILE_SIZE)*0.5f));
	*/
}

Level::~Level()
{
	mTimer = NULL;
	mHUD = NULL;
	/*
	delete mLevelLabel;
	mLevelLabel = NULL;
	delete mLevelNumber;
	mLevelNumber = NULL;
	*/
	mPlayer = NULL; // player is not created in this class so we don't need to destroy it here...OH!

	// delete mReadyLabel;
	// mReadyLabel = NULL;

	/*
	for (Map* m : mMaps)
	{
		delete m; // maps are created in this class
		m = NULL;
	}
	*/
}

void Level::StartLevel()
{
	mLevelStarted = true;
}

/*
void Level::CreateMaps()
{
	const std::string path = "C:\\Users\\Spencer\\Documents\\GitHub\\CIS17B-Final-SimpleSDL\\CIS17B-Final-Mach2\\Debug\\Assets\\";
	mMaps[0] = new Map(mTileSetPath, path + "map00.map", 11, 11);
	//mFxMaps[0] = new Map(mTileSetPath, path + "mapFx00.map", 11, 11);

	mMaps[1] = new Map(mTileSetPath, path + "map01.map", 11, 11);
	//mFxMaps[1] = new Map(mTileSetPath, path + "mapFx01.map", 11, 11);

	mMaps[2] = new Map(mTileSetPath, path + "map02.map", 11, 11);
	//mFxMaps[2] = new Map(mTileSetPath, path + "mapFx02.map", 11, 11);

	mMaps[3] = new Map(mTileSetPath, path + "map03.map", 11, 11);
	//mFxMaps[3] = new Map(mTileSetPath, path + "mapFx03.map", 11, 11);

	mMaps[4] = new Map(mTileSetPath, path + "map04.map", 11, 11);
	//mFxMaps[4] = new Map(mTileSetPath, path + "mapFx04.map", 11, 11);

	mMaps[5] = new Map(mTileSetPath, path + "map05.map", 11, 11);
	//mFxMaps[5] = new Map(mTileSetPath, path + "mapFx05.map", 11, 11);

	mMaps[6] = new Map(mTileSetPath, path + "map06.map", 11, 11);
	//mFxMaps[6] = new Map(mTileSetPath, path + "mapFx06.map", 11, 11);

	mMaps[7] = new Map(mTileSetPath, path + "map07.map", 11, 11);
	//mFxMaps[7] = new Map(mTileSetPath, path + "mapFx07.map", 11, 11);

	mMaps[8] = new Map(mTileSetPath, path + "map08.map", 11, 11);
	//mFxMaps[8] = new Map(mTileSetPath, path + "mapFx08.map", 11, 11);

	mMaps[9] = new Map(mTileSetPath, path + "map09.map", 11, 11);
	//mFxMaps[9] = new Map(mTileSetPath, path + "mapFx09.map", 11, 11);
}
*/

void Level::Update()
{
	if (!mLevelStarted)
	{
		mLabelTimer += mTimer->DeltaTime();
		if (mLabelTimer >= mLevelLabelOffScreen)
		{
			StartLevel();
			if (mLevel > 0) // cautionary
			{
				std::cout << "level is " << mLevel << std::endl;
				// mMaps[mLevel - 1]->LoadMap();
				// mFxMaps[mLevel - 1]->LoadMap();
			}
			mPlayer->Active(true);
			mPlayer->Visible(true);
		}
	}
}

/*
void Level::Render()
{
	if (mLevel > 0)
	{
		mMaps[mLevel - 1]->Render();
		mFxMaps[mLevel - 1]->Render();
	}
	
	
	if (!mLevelStarted)
	{
		if (mLabelTimer > mLevelLabelOnScreen && mLabelTimer < mLevelLabelOffScreen)
		{
			//mLevelLabel->Render();
			//mLevelNumber->Render();
		}
	}
	
}
*/