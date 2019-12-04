#pragma once
#include "HUD.h"
#include "Player.h"
#include <array>
#include "Map.h"

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

	std::string mTileSetPath; // since this is always the same so far
	bool mMapIsLoaded;

public:
	// Array of map objects
	Map* mMaps[10];


private:
	void StartLevel();
	void CreateMaps();

public:
	Level(int level, HUD* hud, Player* player);
	~Level();

	void Update();
	void Render();
};