#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();
	mHUD = HUD::Instance();

	mLevelStartDelay = 1.0f;
	mLevelStarted = false;

	mBeginLabel0 = new Texture(" PREPARE TO ", "forgotmybazookaathome.ttf", 48, { 255,255,255 });
	mBeginLabel1 = new Texture("INVESTIGATE!", "forgotmybazookaathome.ttf", 48, { 255,255,255 });
	mBeginLabel0->Parent(this);
	mBeginLabel1->Parent(this);
	mBeginLabel0->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f - 48));
	mBeginLabel1->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f + 48));
	
	//mStartLabel = new Texture("START!", "forgotmybazookaathome.ttf", 60, { 255,255,255 });
	//mStartLabel->Parent(this);
	//mStartLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
}

PlayScreen::~PlayScreen()
{
	mTimer = NULL;
	mInput = NULL;

	// delete mStartLabel;
	// mStartLabel = NULL;
	delete mBeginLabel0;
	mBeginLabel0 = NULL;
	delete mBeginLabel1;
	mBeginLabel1 = NULL;
}

void PlayScreen::StartNextLevel()
{
	mCurrentLevel++;
	mHUD->SetCurrentScore(mCurrentLevel);
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;
	mAudio->PlayMusic("SMRPG_BarrelVocano_Loop.wav", -1);
}

void PlayScreen::StartNewGame()
{
	mGameStarted = false;
	mLevelStarted = false; // in case this is second go-around
	mAudio->PlayMusic("smrpg_battlestart_padded.wav", 0); //0: no loop, -1(default): infinite loop
	mCurrentLevel = 0;
}

void PlayScreen::Update()
{
	if (mGameStarted && mLevelStarted)
	{
		mHUD->Update();
	}
	else if (mGameStarted)
	{
		if (!mLevelStarted)
		{
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStartDelay)
				StartNextLevel();
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
}

void PlayScreen::Render()
{
	if (!mGameStarted)
	{
		// mStartLabel->Render();
		mBeginLabel0->Render();
		mBeginLabel1->Render();
	}
	if (mLevelStarted)
	{
		mHUD->Render();
	}
}