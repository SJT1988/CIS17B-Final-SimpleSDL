#pragma once
#include "AudioManager.h"
//#include "Level.h"
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
	/* nudges player LEFT and UP (user's POV) so that he is centered about the provided coordinates.
	   For example, when the player is parented to a map object, mPlayer->Pos(VEC2_ZERO) places
	   upper-left corner of his sprite at the map's upper-left corner--but the player's center is
	   to the right 32px and down 32px; to correct this, we OFFSET his position by adding the following
	   vector:	
	*/
	//const Vector2 PLAYER_OFFSET = Vector2(-32.0f, -32.0f);
	Vector2 mStartPos[10];

	const std::string mDirectory = "Debug\\Assets\\";
	std::string mTileSetPath;
	Map* mMaps[10];
	Map* mFxMaps[10];
	Map* mColliderMaps[10];

	// monsters
	std::vector<Monster*>mMonsters;

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