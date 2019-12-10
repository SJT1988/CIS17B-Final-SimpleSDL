#pragma once
#include "StartScreen.h"
#include "PlayScreen.h"
#include "GameOverScreen.h"
#include "Timer.h"

class ScreenManager
{
private:
	Timer* mTimer;
	float GameOverTimer;
	enum SCREENS { start, play, gameOver };
	static ScreenManager* sInstance;
	InputManager* mInput;
	StartScreen* mStartScreen;
	PlayScreen* mPlayScreen;
	GameOverScreen* mGameOverScreen;

	SCREENS mCurrentScreen;

public:

	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();

private:

	ScreenManager();
	~ScreenManager();
};