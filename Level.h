#pragma once
#include "HUD.h"
#include "Player.h"
#include <array>


class Level : public GameEntity
{
private:
	Timer* mTimer;
	HUD* mHUD;

	float mLabelTimer;
	float mLevelLabelOnScreen;
	float mLevelLabelOffScreen;

	int mLevel;
	bool mLevelStarted;
	//Texture* mLevelLabel;
	//ScoreBoard* mLevelNumber;

	Player* mPlayer;

	std::string mTileSetPath; // since this is always the same so far

public:

	
	// Array of map objects
	//Map* mMaps[10];
	//Map* mFxMaps[10];


private:
	void StartLevel();
	//void CreateMaps();

public:
	Level(int level, HUD* hud, Player* player);
	~Level();

	void Update();
	//void Render();
};