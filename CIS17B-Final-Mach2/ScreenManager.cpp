#include "ScreenManager.h"
#include <iostream>

ScreenManager* ScreenManager::sInstance = NULL;

ScreenManager* ScreenManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new ScreenManager();
	}

	return sInstance;
}

void ScreenManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

ScreenManager::ScreenManager()
{
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();
	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();
	mGameOverScreen = new GameOverScreen();
	mCreditsScreen = new CreditsScreen();
	mCurrentScreen = start;
	GameOverTimer = 0.f;
	mTimer = Timer::Instance();
}

ScreenManager::~ScreenManager()
{
	mInput = NULL;

	delete mStartScreen;
	mStartScreen = NULL;

	delete mPlayScreen;
	mPlayScreen = NULL;

	delete mGameOverScreen;
	mGameOverScreen = NULL;
}

void ScreenManager::Update()
{
	switch (mCurrentScreen)
	{
	case start:

		mStartScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_RETURN) && mStartScreen->MenuSelection() == 0)
		{
			mCurrentScreen = play;
			if (mStartScreen) delete mStartScreen;
			mStartScreen = new StartScreen();
			mPlayScreen->StartNewGame();
		}
		else if (mInput->KeyPressed(SDL_SCANCODE_RETURN) && mStartScreen->MenuSelection() == 1)
		{
			mAudio->PlaySFX("FF7_CursorOk.wav");
			mCurrentScreen = credits;
			if (mStartScreen) delete mStartScreen;
			mStartScreen = new StartScreen();
		}
		break;

	case play:
		mPlayScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE))
		{
			if (Mix_PlayingMusic())
			{
				Mix_FadeOutMusic(500);
				Mix_RewindMusic();
			}

			mCurrentScreen = start;
			if (mPlayScreen) delete mPlayScreen;
			mPlayScreen = new PlayScreen;
		}
		else if (mPlayScreen->mDead == true)
		{
			if (Mix_PlayingMusic())
			{
				Mix_FadeOutMusic(500);
				Mix_RewindMusic();
			}

			mCurrentScreen = gameOver;
			if (mPlayScreen) delete mPlayScreen;
			mPlayScreen = new PlayScreen;
		}
		break;

	case gameOver:
		mGameOverScreen->Update();
		GameOverTimer += mTimer->DeltaTime();

		if (GameOverTimer >= 3) {
			GameOverTimer = 0;
			mCurrentScreen = start;
		}
		break;

	case credits:
		mCreditsScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE))
		{
			mCurrentScreen = start;
			if (mCreditsScreen) delete mCreditsScreen;
			mCreditsScreen = new CreditsScreen;
		}
	}
}

void ScreenManager::Render()
{
	switch (mCurrentScreen)
	{
	case start:
		mStartScreen->Render();
		break;

	case play:
		mPlayScreen->Render();
		break;

	case gameOver:
		mGameOverScreen->Render();
		break;

	case credits:
		mCreditsScreen->Render();
	}
}