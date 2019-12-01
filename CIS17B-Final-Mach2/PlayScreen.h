#pragma once
#include "InputManager.h"
#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "HUD.h"
#include "GameEntity.h"

using namespace QuickSDL;

class PlayScreen : public GameEntity
{
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;
	HUD* mHUD;

	// Texture* mStartLabel;
	Texture* mBeginLabel0;
	Texture* mBeginLabel1;
	float mLevelStartTimer;
	float mLevelStartDelay;

	bool mGameStarted;
	bool mLevelStarted;
	int mCurrentLevel;

private:

	void StartNextLevel();


public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame();

	void Update();
	void Render();
};