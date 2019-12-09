#pragma once
#include "ScoreBoard.h"
#include "Timer.h"

using namespace QuickSDL;

class HUD : public GameEntity
{
private:
	Timer* mTimer;

	GameEntity* mTopBar;
	Texture* mCurrentDepth;
	Texture* mDeepestDepth;
	ScoreBoard* mScore;
	ScoreBoard* mHighScore;

public:

	HUD();
	~HUD();

	void SetCurrentScore(int score);
	void SetHighScore(int score);

	void Update();
	void Render();
};