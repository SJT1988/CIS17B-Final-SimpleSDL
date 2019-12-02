#include "Level.h"

Level::Level(int level, HUD* hud, Player* player)
{
	mTimer = Timer::Instance();
	mHUD = hud;
	mHUD->SetCurrentScore(level);

	mLevel = level;
	mLevelStarted = false;
	mLabelTimer = 0.0f;

	mLevelLabel = new Texture("LEVEL", "forgotmybazookaathome.ttf", 24, { 64,0,255 });
	mLevelLabel->Parent(this);
	mLevelLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f - 13, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	mLevelNumber = new ScoreBoard({64, 64, 255 });
	mLevelNumber->Score(mLevel);
	mLevelNumber->Parent(this);
	mLevelNumber->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f + 123, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	mLevelLabelOnScreen = 0.0f;
	mLevelLabelOffScreen = 1.5f;

	mPlayer = player;

	//ReadyLabel stuff here ends at 30:40 in Galaga - 8
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
}

void Level::StartLevel()
{
	mLevelStarted = true;
}

void Level::Update()
{
	if (!mLevelStarted)
	{
		mLabelTimer += mTimer->DeltaTime();
		if (mLabelTimer >= mLevelLabelOffScreen)
		{
			StartLevel();
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
}