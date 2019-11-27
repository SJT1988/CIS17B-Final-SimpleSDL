#include "ScreenManager.h"

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

	mCurrentScreen = start;
}

ScreenManager::~ScreenManager()
{
	mInput = NULL;

	delete mStartScreen;
	mStartScreen = NULL;
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
			mStartScreen->~StartScreen();
			mStartScreen->ResetAnimation();
		}
		break;

	case play:

		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE))
		{
			mStartScreen = new StartScreen();
			mCurrentScreen = start;
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
	}
}