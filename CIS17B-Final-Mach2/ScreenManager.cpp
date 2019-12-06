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
	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();
	mCurrentScreen = start;
}

ScreenManager::~ScreenManager()
{
	mInput = NULL;

	delete mStartScreen;
	mStartScreen = NULL;

	delete mPlayScreen;
	mPlayScreen = NULL;
}

void ScreenManager::Update()
{
	switch (mCurrentScreen)
	{
	case start:

		mStartScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_RETURN))
		{
			mCurrentScreen = play;
			if (mStartScreen) delete mStartScreen;
			mStartScreen = new StartScreen();
			//mStartScreen->ResetAnimation();
			mPlayScreen->StartNewGame();
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
		break;
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
	}
}