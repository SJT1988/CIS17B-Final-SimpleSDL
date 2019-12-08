#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();
	mHUD = new HUD();

	mLevelStartDelay = 1.0f;
	mLevelStarted = false;

	mBeginLabel0 = new Texture(" PREPARE TO ", "forgotmybazookaathome.ttf", 48, { 255,255,255 });
	mBeginLabel1 = new Texture("INVESTIGATE!", "forgotmybazookaathome.ttf", 48, { 255,255,255 });
	mBeginLabel0->Parent(this);
	mBeginLabel1->Parent(this);
	mBeginLabel0->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f - 48));
	mBeginLabel1->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f + 48));

	//==============
	mLevelLabel = new Texture("LEVEL", "forgotmybazookaathome.ttf", 24, { 64,64,255 });
	mLevelLabel->Parent(this);
	mLevelLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f - 13, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	mLevelNumber = new ScoreBoard({ 64, 64, 255 });
	mLevelNumber->Score(mCurrentLevel);
	mLevelNumber->Parent(this);
	mLevelNumber->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f + 123, Graphics::Instance()->SCREEN_HEIGHT*0.5f));
	//==============

	mPlayer = NULL;

	// Map stuff
	mTileSetPath = "tilesetDarker.png";
	CreateMaps();

	for (Map* m : mMaps)
		m->Pos(Vector2((Graphics::Instance()->SCREEN_WIDTH - m->mSizeX * m->TILE_SIZE)*0.5f,
		(Graphics::Instance()->SCREEN_HEIGHT - m->mSizeY * m->TILE_SIZE)*0.5f));

	for (Map* fx : mFxMaps)
		fx->Pos(Vector2((Graphics::Instance()->SCREEN_WIDTH - fx->mSizeX * fx->TILE_SIZE)*0.5f,
		(Graphics::Instance()->SCREEN_HEIGHT - fx->mSizeY * fx->TILE_SIZE)*0.5f));

	for (Map* col : mColliderMaps)
		col->Pos(Vector2((Graphics::Instance()->SCREEN_WIDTH - col->mSizeX * col->TILE_SIZE)*0.5f,
		(Graphics::Instance()->SCREEN_HEIGHT - col->mSizeY * col->TILE_SIZE)*0.5f));
}

PlayScreen::~PlayScreen()
{
	mTimer = NULL;
	mInput = NULL;

	delete mHUD;
	mHUD = NULL;

	delete mBeginLabel0;
	mBeginLabel0 = NULL;
	delete mBeginLabel1;
	mBeginLabel1 = NULL;

	delete mPlayer;
	mPlayer = NULL;

	//==============
	delete mLevelLabel;
	mLevelLabel = NULL;
	delete mLevelNumber;
	mLevelNumber = NULL;
	//==============

	for (Map* m : mMaps)
	{
		delete m;
		m = NULL;
	}
	
	for (Map* m : mFxMaps)
	{
		delete m;
		m = NULL;
	}

	for (Map* m : mColliderMaps)
	{
		delete m;
		m = NULL;
	}

	for (Monster* m : mMonsters)
	{
		delete m;
		m = NULL;
	}
}

void PlayScreen::StartNextLevel()
{
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;
	if (mCurrentLevel == 1)
		mAudio->PlayMusic("SMRPG_BarrelVocano_LH.wav", -1);
	if (mCurrentLevel > 0)
	{
		mMaps[mCurrentLevel - 1]->LoadMap();
		mFxMaps[mCurrentLevel - 1]->LoadMap();
		mColliderMaps[mCurrentLevel - 1]->LoadColliders(mDirectory + mColliderMaps[mCurrentLevel - 1]->mMapFilePath);
	}

	// Create monster
	mMonsters.emplace_back(new Monster(80.0f, 120.0f));
	mMonsters.back()->Parent(mMaps[mCurrentLevel - 1]);
	mMonsters.back()->Pos(VEC2_ZERO);

	mMonsters.emplace_back(new Monster(120.0f, 160.0f));
	mMonsters.back()->Parent(mMaps[mCurrentLevel - 1]);
	mMonsters.back()->Pos(Vector2(16.0f,16.0f));

	mMonsters.emplace_back(new Monster(60.0f, 100.0f));
	mMonsters.back()->Parent(mMaps[mCurrentLevel - 1]);
	mMonsters.back()->Pos(Vector2(32.0f,32.0f));

	mMonsters.emplace_back(new Monster(0.0f, 0.0f));
	mMonsters.back()->Parent(mMaps[mCurrentLevel - 1]);
	mMonsters.back()->Pos(Vector2(64.0f, 64.0f));
}

void PlayScreen::StartNewGame()
{
	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mPlayer->Active(false);

	mCurrentLevel = 0;
	mHUD->SetCurrentScore(0);
	mGameStarted = false;
	mLevelStarted = false; // in case this is second go-around
	mAudio->PlayMusic("smrpg_battlestart_padded.wav", 0); //0: no loop, -1(default): infinite loop
}

void PlayScreen::CreateMaps()
{
	mMaps[0] = new Map(mTileSetPath, mDirectory + "map00.map", 11, 11);
	mFxMaps[0] = new Map(mTileSetPath, mDirectory + "mapFx00.map", 11, 11);
	mColliderMaps[0] = new Map(mTileSetPath, mDirectory + "colliders00.map", 11, 11);

	mMaps[1] = new Map(mTileSetPath, mDirectory + "map01.map", 11, 11);
	mFxMaps[1] = new Map(mTileSetPath, mDirectory + "mapFx01.map", 11, 11);
	mColliderMaps[1] = new Map(mTileSetPath, mDirectory + "colliders01.map", 11, 11);

	mMaps[2] = new Map(mTileSetPath, mDirectory + "map02.map", 11, 11);
	mFxMaps[2] = new Map(mTileSetPath, mDirectory + "mapFx02.map", 11, 11);
	mColliderMaps[2] = new Map(mTileSetPath, mDirectory + "colliders02.map", 11, 11);

	mMaps[3] = new Map(mTileSetPath, mDirectory + "map03.map", 11, 11);
	mFxMaps[3] = new Map(mTileSetPath, mDirectory + "mapFx03.map", 11, 11);
	mColliderMaps[3] = new Map(mTileSetPath, mDirectory + "colliders03.map", 11, 11);

	mMaps[4] = new Map(mTileSetPath, mDirectory + "map04.map", 11, 11);
	mFxMaps[4] = new Map(mTileSetPath, mDirectory + "mapFx04.map", 11, 11);
	mColliderMaps[4] = new Map(mTileSetPath, mDirectory + "colliders04.map", 11, 11);

	mMaps[5] = new Map(mTileSetPath, mDirectory + "map05.map", 11, 11);
	mFxMaps[5] = new Map(mTileSetPath, mDirectory + "mapFx05.map", 11, 11);
	mColliderMaps[5] = new Map(mTileSetPath, mDirectory + "colliders05.map", 11, 11);

	mMaps[6] = new Map(mTileSetPath, mDirectory + "map06.map", 11, 11);
	mFxMaps[6] = new Map(mTileSetPath, mDirectory + "mapFx06.map", 11, 11);
	mColliderMaps[6] = new Map(mTileSetPath, mDirectory + "colliders06.map", 11, 11);

	mMaps[7] = new Map(mTileSetPath, mDirectory + "map07.map", 11, 11);
	mFxMaps[7] = new Map(mTileSetPath, mDirectory + "mapFx07.map", 11, 11);
	mColliderMaps[7] = new Map(mTileSetPath, mDirectory + "colliders07.map", 11, 11);

	mMaps[8] = new Map(mTileSetPath, mDirectory + "map08.map", 11, 11);
	mFxMaps[8] = new Map(mTileSetPath, mDirectory + "mapFx08.map", 11, 11);
	mColliderMaps[8] = new Map(mTileSetPath, mDirectory + "colliders08.map", 11, 11);

	mMaps[9] = new Map(mTileSetPath, mDirectory + "map09.map", 11, 11);
	mFxMaps[9] = new Map(mTileSetPath, mDirectory + "mapFx09.map", 11, 11);
	mColliderMaps[9] = new Map(mTileSetPath, mDirectory + "colliders09.map", 11, 11);
}

void PlayScreen::Update()
{
	if (mGameStarted && mLevelStarted)
	{
		mPlayer->Update();
		for (Monster* m : mMonsters)
		{
			m->Update();
			m->Move(mPlayer->Pos());
		}

		if (mInput->KeyPressed(SDL_SCANCODE_N))
		{
			mLevelStarted = false;
			mPlayer->Active(false);
			mPlayer->Visible(false);
			for (Monster* m : mMonsters)
			{
				delete m;
				m = NULL;
			}
		}
	}
	else if (mGameStarted)
	{
		if (!mLevelStarted)
		{
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStartDelay)
			{
				StartNextLevel();
				mPlayer->Active(true);
				mPlayer->Visible(true);
			}
		}
	}
	else
	{
		// WARNING! This test will fail if it is testing "music" played with PlaySFX()
		if (!Mix_PlayingMusic())
		{
			mGameStarted = true;
		}
	}
	//std::cout << "GameStarted: " << mGameStarted << std::endl;
	//std::cout << "LevelStarted: " << mLevelStarted << std::endl;
	//system("CLS");
}

void PlayScreen::Render()
{

	if (!mGameStarted)
	{
		mBeginLabel0->Render();
		mBeginLabel1->Render();
	}
	if (mGameStarted)
	{
		if (!mLevelStarted)
		{
			if (mLevelStartTimer == 0)
			{
				mCurrentLevel++;
				mLevelNumber->Score(mCurrentLevel);
				mHUD->SetCurrentScore(mCurrentLevel);
			}
			if (mLevelStartTimer > 0.0f && mLevelStartTimer < mLevelStartDelay)
			{
				mLevelLabel->Render();
				mLevelNumber->Render();
			}
		}
		if (mLevelStarted)
		{
			if (mCurrentLevel > 0)
				mMaps[mCurrentLevel - 1]->Render();
			mPlayer->Active(true);
			mPlayer->Visible(true);
			mPlayer->Render();
			for (Monster* m : mMonsters)
			{
				m->Render();
			}
			if (mCurrentLevel > 0)
			{
				mFxMaps[mCurrentLevel - 1]->Render();
				mColliderMaps[mCurrentLevel - 1]->Render();
			}
		}
		mHUD->Render();
	}
}