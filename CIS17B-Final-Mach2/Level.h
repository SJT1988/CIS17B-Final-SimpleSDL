#pragma once
#include "HUD.h"
#include "Player.h"

class Level : public GameEntity
{
private:
	Timer* mTimer;
	HUD* mHUD;

	int mLevel;
	bool mLevelStarted;
	float mLabelTimer;
	Texture* mLevelLabel;
	// Texture* mReadyLabel;
	ScoreBoard* mLevelNumber;
	float mLevelLabelOnScreen;
	float mLevelLabelOffScreen;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	Player* mPlayer;

private:
	void StartLevel();

public:
	Level(int level, HUD* hud, Player* player);
	~Level();

	void Update();
	void Render();
};