#pragma once
#include "InputManager.h"
#include "AnimatedTexture.h"
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

<<<<<<< Updated upstream
=======
	

>>>>>>> Stashed changes
private:

	void StartNextLevel();


public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame();
	Player* mPlayer;

	void Update();
	void Render();
};