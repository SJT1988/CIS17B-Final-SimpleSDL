#pragma once
#include "ScoreBoard.h"
#include "Timer.h"

using namespace QuickSDL;

class HUD : public GameEntity
{
private:
	Timer* mTimer;
	static HUD* sInstance;

	GameEntity* mTopBar;
	Texture* mCurrentDepth;
	Texture* mDeepestDepth;
	ScoreBoard* mScore;
	ScoreBoard* mHighScore;

private:

	HUD();
	~HUD();

public:

	static HUD* Instance();
	static void Release();

	void SetCurrentScore(int score);
	void SetHighScore(int score);

	void Update();
	void Render();
};