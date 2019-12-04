#pragma once
#include "AudioManager.h"
#include "Level.h"
#include "GameEntity.h"
#include "Map.h"

using namespace QuickSDL;

class PlayScreen : public GameEntity
{
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;
	HUD* mHUD;

	// "PREPARE TO INVESTIGATE!"
	Texture* mBeginLabel0;
	Texture* mBeginLabel1;
	float mLevelStartTimer;
	float mLevelStartDelay;

	// "Level N"
	Texture* mLevelLabel;
	ScoreBoard* mLevelNumber;

	Level* mLevel;
	bool mGameStarted;
	bool mLevelStarted;
	int mCurrentLevel;

	Player* mPlayer;

	std::string mTileSetPath;
	Map* mMaps[10];
	Map* mFxMaps[10];

private:

	void StartNextLevel();
	void CreateMaps();


public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame();

	void Update();
	void Render();
};