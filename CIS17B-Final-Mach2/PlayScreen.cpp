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
	mLevelLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f - 13, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mLevelNumber = new ScoreBoard({ 64, 64, 255 });
	mLevelNumber->Score(mCurrentLevel);
	mLevelNumber->Parent(this);
	mLevelNumber->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f + 123, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	//==============

	mPlayer = NULL;

	// Map stuff
	mTileSetPath = "tileset3.png";
	CreateMaps();

	for (Map* m : mMaps)
		m->Pos(Vector2((Graphics::Instance()->SCREEN_WIDTH - m->mSizeX * m->TILE_SIZE) * 0.5f,
		(Graphics::Instance()->SCREEN_HEIGHT - m->mSizeY * m->TILE_SIZE) * 0.5f + 32.0f));

	for (Map* fx : mFxMaps)
		fx->Pos(Vector2((Graphics::Instance()->SCREEN_WIDTH - fx->mSizeX * fx->TILE_SIZE) * 0.5f,
		(Graphics::Instance()->SCREEN_HEIGHT - fx->mSizeY * fx->TILE_SIZE) * 0.5f + 32.0f));
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

	for (Monster* m : mMonsters)
	{
		delete m;
		m = NULL;
	}
}

void PlayScreen::StartNextLevel()
{
	mPlayer->Parent(mMaps[mCurrentLevel - 1]);
	mPlayer->Pos(VEC2_ZERO);
	//std::cout << mPlayer->Pos(local) << std::endl;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;
	if (mCurrentLevel == 1)
		mAudio->PlayMusic("SMRPG_BarrelVocano_LH.wav", -1);
	if (mCurrentLevel > 0)
	{
		mMaps[mCurrentLevel - 1]->LoadMap();
		mMaps[mCurrentLevel - 1]->CreateColliders(mColliderPaths[mCurrentLevel - 1]);
		mFxMaps[mCurrentLevel - 1]->LoadMap();
		mPlayer->Pos(mStartPos[mCurrentLevel - 1]);
		mPlayerTempPos = mStartPos[mCurrentLevel - 1];
		//std::cout << mPlayer->Pos(local) << std::endl;
	}

	// Delete previous monsters:
	if (!mMonsters.empty())
	{
		mMonsters.clear();
	}
	// Create new monsters:
	CreateMonsters(mCurrentLevel);

	mPlayer->Active(true);
	mPlayer->Visible(true);
	for (Monster* m : mMonsters)
	{
		m->Active(true);
	}

	// delete unneeded maps:
	if (mCurrentLevel > 1)
	{
		delete mMaps[mCurrentLevel - 2];
		mMaps[mCurrentLevel - 2] = NULL;

		delete mFxMaps[mCurrentLevel - 2];
		mFxMaps[mCurrentLevel - 2] = NULL;
	}
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
	const std::string path = "Debug\\Assets\\";
	mMaps[0] = new Map(mTileSetPath, path + "map00.map", 15, 15, 0);
	mFxMaps[0] = new Map(mTileSetPath, path + "mapFx00.map", 15, 15);
	mColliderPaths[0] = path + "colliders00.map";
	mStartPos[0] = Vector2(32.0f, 32.0f);

	mMaps[1] = new Map(mTileSetPath, path + "map01.map", 21, 21, 1);
	mFxMaps[1] = new Map(mTileSetPath, path + "mapFx01.map", 21, 21);
	mColliderPaths[1] = path + "colliders01.map";
	mStartPos[1] = Vector2(416.0f, 416.0f);

	mMaps[2] = new Map(mTileSetPath, path + "map02.map", 31, 11, 2);
	mFxMaps[2] = new Map(mTileSetPath, path + "mapFx02.map", 31, 11);
	mColliderPaths[2] = path + "colliders02.map";
	mStartPos[2] = Vector2(32, 32);
	//mStartPos[2] = Vector2(928, 288);

	mMaps[3] = new Map(mTileSetPath, path + "map03.map", 31, 15, 3);
	mFxMaps[3] = new Map(mTileSetPath, path + "mapFx03.map", 31, 15);
	mColliderPaths[3] = path + "colliders03.map";
	mStartPos[3] = Vector2(32.0f, 32.0f);


	mMaps[4] = new Map(mTileSetPath, path + "map04.map", 21, 21, 4);
	mFxMaps[4] = new Map(mTileSetPath, path + "mapFx04.map", 21, 21);
	mColliderPaths[4] = path + "colliders04.map";
	mStartPos[4] = Vector2(608.0f, 608.0f); //Vector2(32, 96);


	mMaps[5] = new Map(mTileSetPath, path + "map05.map", 39, 19, 5);
	mFxMaps[5] = new Map(mTileSetPath, path + "mapFx05.map", 39, 19);
	mColliderPaths[5] = path + "colliders05.map";
	mStartPos[5] = Vector2(96.0f, 32.0f);


	mMaps[6] = new Map(mTileSetPath, path + "map06.map", 31, 21, 6);
	mFxMaps[6] = new Map(mTileSetPath, path + "mapFx06.map", 31, 21);
	mColliderPaths[6] = path + "colliders06.map";
	mStartPos[6] = Vector2(928.0f, 544.0f); // Vector2(32, 32);


	mMaps[7] = new Map(mTileSetPath, path + "map07.map", 39, 21, 7);
	mFxMaps[7] = new Map(mTileSetPath, path + "mapFx07.map", 39, 21);
	mColliderPaths[7] = path + "colliders07.map";
	mStartPos[7] = Vector2(32.0f, 32.0f);

	mMaps[8] = new Map(mTileSetPath, path + "map08.map", 15, 15, 8);
	mFxMaps[8] = new Map(mTileSetPath, path + "mapFx08.map", 15, 15);
	mColliderPaths[8] = path + "colliders08.map";
	mStartPos[8] = Vector2(416.0f, 416.0f);

	mMaps[9] = new Map(mTileSetPath, path + "map09.map", 39, 21, 9);
	mFxMaps[9] = new Map(mTileSetPath, path + "mapFx09.map", 39, 21);
	mColliderPaths[9] = path + "colliders09.map";
	mStartPos[9] = Vector2(1184, 32);

}

void PlayScreen::MonsterSpawner(int row, int col) {
	float tempScale = RandomFloat(0.5f, 1.5f);
	float tempSpeed = 120.f + RandomFloat(-60.0f,40.0f);
	mMonsters.push_back(new Monster(0.0f, tempSpeed));
	mMonsters.back()->Scale(Vector2(tempScale, tempScale));
	mMonsters.back()->Parent(mMaps[mCurrentLevel - 1]);
	mMonsters.back()->Pos(Vector2(row * 32, col * 32));

}

void PlayScreen::CreateMonsters(int currentLevel)
{
	switch (currentLevel)
	{
		//map00.map
	case 1: //1313
		MonsterSpawner( 1, 1);
		MonsterSpawner( 6, 13);
		MonsterSpawner( 7, 9);
		MonsterSpawner( 13, 13);
		break;
		//map01.map
	case 2: //1019
		MonsterSpawner( 1, 1);
		MonsterSpawner( 4, 19);
		MonsterSpawner( 19, 1);
		break;
		//map02.map
	case 3: //929
		MonsterSpawner( 15, 1);
		MonsterSpawner( 19, 9);
		MonsterSpawner( 24, 1);
		MonsterSpawner( 25, 4);
		MonsterSpawner( 22, 9);
		break;
	case 4: //2813
		MonsterSpawner( 8, 8);
		MonsterSpawner( 9, 11);
		MonsterSpawner( 16, 7);
		MonsterSpawner( 12, 10);
		MonsterSpawner( 18, 12);
		MonsterSpawner( 24, 3);
		MonsterSpawner( 25, 6);
		MonsterSpawner( 27, 11);

		break;
	case 5: // 1919
		MonsterSpawner( 2, 12);
		MonsterSpawner( 4, 17);
		MonsterSpawner( 8, 10);
		MonsterSpawner( 13, 16);
		MonsterSpawner( 15, 3);
		MonsterSpawner( 17, 11);
		MonsterSpawner( 1, 15);
		break;
	case 6: //2816
		MonsterSpawner( 3, 14);
		MonsterSpawner( 6, 16);
		MonsterSpawner( 9, 16);
		MonsterSpawner( 11, 9);
		MonsterSpawner( 12, 15);
		MonsterSpawner( 13, 2);
		MonsterSpawner( 14, 7);
		MonsterSpawner( 16, 4);
		MonsterSpawner( 20, 9);
		MonsterSpawner( 22, 15);
		break;
	case 7: //1929
		MonsterSpawner( 1, 1);
		MonsterSpawner( 5, 7);
		MonsterSpawner( 2, 11);
		MonsterSpawner( 4, 19);
		MonsterSpawner( 4, 12);
		MonsterSpawner( 8, 6);
		MonsterSpawner( 14, 1);
		MonsterSpawner( 18, 13);
		MonsterSpawner( 21, 4);
		MonsterSpawner( 23, 3);
		MonsterSpawner( 22, 15);
		break;
	case 8: //3719
		MonsterSpawner( 9, 15);
		MonsterSpawner( 12, 1);
		MonsterSpawner( 14, 9);
		MonsterSpawner( 16, 3);
		MonsterSpawner( 19, 18);
		MonsterSpawner( 21, 6);
		MonsterSpawner( 25, 3);
		MonsterSpawner( 26, 7);
		MonsterSpawner( 27, 9);
		MonsterSpawner( 30, 7);
		MonsterSpawner( 32, 14);

		break;
	case 9: //1313
		MonsterSpawner( 1, 1);
		MonsterSpawner( 3, 4);
		MonsterSpawner( 2, 8);
		MonsterSpawner( 4, 13);
		MonsterSpawner( 7, 1);
		MonsterSpawner( 6, 4);
		MonsterSpawner( 13, 1);
		MonsterSpawner( 11, 4);
		break;
	case 10://1938
		for (int i = 1; i < 35; i += (7 + static_cast<int>(RandomFloat(-1.0f,2.0f))))
		{
			for (int j = 1; j < 17; j += (5 + static_cast<int>(RandomFloat(-1.0f, 2.0f))))
			{
				MonsterSpawner( i, j);
			}
		}
		break;
	default:
		break;
	}
}

void PlayScreen::ResolvePlayerCollision()
{
	bool playerCollision = false;

	// Handle collision with walls and mushrooms:
	for (Collider* c : mMaps[mCurrentLevel - 1]->mColliders1)
	{
		if (Collider::AABB(mPlayer->mCollider, c))
		{
			playerCollision = true;
			mPlayer->Pos(mPlayerTempPos);
			break;
		}
	}
	if (playerCollision == false)
		mPlayerTempPos = mPlayer->Pos(local);

	// Handle collision with Monsters and Spikes:
	for (Collider* c : mMaps[mCurrentLevel - 1]->mColliders3)
	{
		if (Collider::AABB(mPlayer->mCollider, c))
		{
			std::cout << "DEATH BY SPIKES!" << std::endl;
			break;
		}
	}
	for (Monster* m : mMonsters)
	{
		if (Collider::AABB(mPlayer->mCollider, m->mCollider))
		{
			std::cout << "DEATH BY MONSTER!" << std::endl;
		}
	}

	// Handle collision with Webs:
	for (Collider* c : mMaps[mCurrentLevel - 1]->mColliders2)
	{
		if (Collider::AABB(mPlayer->mCollider, c))
		{
			std::cout << "STUCK!" << std::endl;
			break;
		}
	}
}

void PlayScreen::Update()
{
	// std::cout << mPlayer->Pos(local) << std::endl;
	if (mGameStarted && mLevelStarted)
	{
		mPlayer->Update();
		for (Monster* m : mMonsters)
		{
			m->Update();
			m->Move(mPlayer->Pos());			
		}
		
		if (mCurrentLevel > 0)
			ResolvePlayerCollision();
		

		if (mInput->KeyPressed(SDL_SCANCODE_N))
		{
			mLevelStarted = false;
			mPlayer->Active(false);
			mPlayer->Visible(false);
			
			for (Monster* m : mMonsters)
			{
				m->Active(false);
			}
		}
	}
	else if (mGameStarted)
	{
		if (!mLevelStarted)
		{
			mLevelStartTimer += mTimer->DeltaTime();
			// this means level is starting:
			if (mLevelStartTimer >= mLevelStartDelay)
			{
				StartNextLevel();
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
				mFxMaps[mCurrentLevel - 1]->Render();
		}
		mHUD->Render();
	}
}