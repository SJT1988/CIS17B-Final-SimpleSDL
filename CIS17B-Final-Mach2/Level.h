#pragma once
#include "InputManager.h"
#include "HUD.h"

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

private:
	void StartLevel();

public:
	Level(int level, HUD* hud);
	~Level();

	void Update();
	void Render();
};