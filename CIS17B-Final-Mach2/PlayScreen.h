#pragma once
#include "AudioManager.h"
#include "Level.h"
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

	Level* mLevel;
	bool mGameStarted;
	bool mLevelStarted;
	int mCurrentLevel;

	Player* mPlayer;

private:

	void StartNextLevel();


public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame();

	void Update();
	void Render();
};