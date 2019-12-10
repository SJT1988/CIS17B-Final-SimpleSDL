#pragma once

#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "ScoreBoard.h"

using namespace QuickSDL;

class GameOverScreen : public GameEntity
{
private:

	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;
	float totalTime = 4.f;

	// Top bar entities
	GameEntity* mTopBar;
	Texture* mCurrentDepth;
	Texture* mDeepestDepth;
	Texture* mGameOver;
	ScoreBoard* mScore;
	ScoreBoard* mHighScore;

public:
	GameOverScreen();
	~GameOverScreen();

	void Update();
	void Render();
};