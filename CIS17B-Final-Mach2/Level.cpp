#include "Level.h"

Level::Level(int level, HUD* hud, Player* player)
{
	mTimer = Timer::Instance();
	mHUD = hud;
	mHUD->SetCurrentScore(level);

	mLevel = level;
	mLevelStarted = false;
	mLabelTimer = 0.0f;

	mLevelLabel = new Texture("LEVEL", "forgotmybazookaathome.ttf", 24, { 64,64,255 });
	mLevelLabel->Parent(this);
	mLevelLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f - 13, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	mLevelNumber = new ScoreBoard({64, 64, 255 });
	mLevelNumber->Score(mLevel);
	mLevelNumber->Parent(this);
	mLevelNumber->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f + 123, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	mLevelLabelOnScreen = 0.0f;
	mLevelLabelOffScreen = 1.5f;

	mPlayer = player;

	// Map stuff
	mTileSetPath = "tileset.png";
	CreateMaps();
	mMapIsLoaded = false;
}

Level::~Level()
{
	mTimer = NULL;
	mHUD = NULL;

	delete mLevelLabel;
	mLevelLabel = NULL;
	delete mLevelNumber;
	mLevelNumber = NULL;

	mPlayer = NULL; // player is not created in this class so we don't need to destroy it here...OH!

	// delete mReadyLabel;
	// mReadyLabel = NULL;

	for (Map* m : mMaps)
	{
		delete m; // maps are created in this class
		m = NULL;
	}

}

void Level::StartLevel()
{
	mLevelStarted = true;
}

void Level::CreateMaps()
{
	mMaps[0] = new Map(mTileSetPath, "map00.map", 11, 11);
	mMaps[1] = new Map(mTileSetPath, "map01.map", 11, 11);
	mMaps[2] = new Map(mTileSetPath, "map02.map", 11, 11);
	mMaps[3] = new Map(mTileSetPath, "map03.map", 11, 11);
	mMaps[4] = new Map(mTileSetPath, "map04.map", 11, 11);
	mMaps[5] = new Map(mTileSetPath, "map05.map", 11, 11);
	mMaps[6] = new Map(mTileSetPath, "map06.map", 11, 11);
	mMaps[7] = new Map(mTileSetPath, "map07.map", 11, 11);
	mMaps[8] = new Map(mTileSetPath, "map08.map", 11, 11);
	mMaps[9] = new Map(mTileSetPath, "map09.map", 11, 11);
}

void Level::Update()
{
	if (!mLevelStarted)
	{
		mLabelTimer += mTimer->DeltaTime();
		if (mLabelTimer >= mLevelLabelOffScreen)
		{
			StartLevel();
			if (mLevel > 0) // cautionary
				std::cout << "level is " << mLevel << std::endl;
				mMaps[mLevel - 1]->LoadMap();
			/*
			if (!mMapIsLoaded)
			{
				mMaps[mLevel - 1]->LoadMap();
				mMapIsLoaded == true;
			}
			*/
			mPlayer->Active(true);
			mPlayer->Visible(true);
		}
	}
}

void Level::Render()
{
	if (!mLevelStarted)
	{
		if (mLabelTimer > mLevelLabelOnScreen && mLabelTimer < mLevelLabelOffScreen)
		{
			mLevelLabel->Render();
			mLevelNumber->Render();
		}
	}
	else
	{
		if (mLevel > 0)
			mMaps[mLevel - 1]->Render();
	}
}