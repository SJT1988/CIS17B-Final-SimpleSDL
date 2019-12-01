#include "Level.h"

Level::Level(int level, HUD* hud)
{
	mTimer = Timer::Instance();
	mHUD = hud;
	mHUD->SetCurrentScore(level);

	mLevel = level;
	mLevelStarted = false;
	mLabelTimer = 0.0f;

	mLevelLabel = new Texture("LEVEL", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	mLevelLabel->Parent(this);
	mLevelLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f - 128, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	mLevelNumber = new ScoreBoard({64, 64, 255 });
	mLevelNumber->Score(mLevel);
	mLevelNumber->Parent(this);
	mLevelNumber->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f + 128, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	mLevelLabelOnScreen = 0.0f;
	mLevelLabelOffScreen = 1.5f;

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
	// delete mReadyLabel;
	// mReadyLabel = NULL;
}

void Level::StartLevel()
{

}

void Level::Update()
{
	if (!mLevelStarted)
	{
		mLabelTimer += mTimer->DeltaTime();
		if (mLabelTimer >= mLevelLabelOffScreen)
		{
			if (mLevel > 1)
			{
				StartLevel();
			}
		}
	}
}

void Level::Render()
{
	mLevelLabel->Render();
	mLevelNumber->Render();
}