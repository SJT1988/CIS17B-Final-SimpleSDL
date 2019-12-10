#pragma once
#include "AudioManager.h"
#include "GameEntity.h"
#include "Map.h"
#include "HUD.h"
#include "Player.h"
#include "Monster.h"

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

	//Level* mLevel;
	bool mGameStarted;
	bool mLevelStarted;
	int mCurrentLevel;

	Player* mPlayer;
	Vector2 mPlayerTempPos;
	float mStuckTimer;
	
	//=====================
	// Map stuff

	Vector2 mStartPos[10];

	const std::string mDirectory = "Debug\\Assets\\";
	std::string mTileSetPath;
	Map* mMaps[10];
	Map* mFxMaps[10];
	//Map* mColliderMaps[10];
	std::string mColliderPaths[10];

	// monsters
	std::vector<Monster*>mMonsters;

private:

	void StartNextLevel();
	void CreateMaps();

	void MonsterSpawner(int x, int y);
	void CreateMonsters(int currentLevel);

	void ResolvePlayerCollision();

public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame();

	void Update();
	void Render();
};