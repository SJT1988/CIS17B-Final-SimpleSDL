#pragma once
#include "StartScreen.h"
#include "PlayScreen.h"
#include "GameOverScreen.h"
#include "CreditsScreen.h"
#include "Timer.h"
#include "AudioManager.h"

class ScreenManager
{
private:
	Timer* mTimer;
	AudioManager* mAudio;
	float GameOverTimer;
	enum SCREENS { start, play, gameOver, credits};
	static ScreenManager* sInstance;
	InputManager* mInput;
	StartScreen* mStartScreen;
	PlayScreen* mPlayScreen;
	GameOverScreen* mGameOverScreen;
	CreditsScreen* mCreditsScreen;

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