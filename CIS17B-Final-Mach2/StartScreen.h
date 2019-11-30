#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "ScoreBoard.h"

using namespace QuickSDL;

class StartScreen : public GameEntity
{
private:

	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	// Top bar entities
	GameEntity* mTopBar;
	Texture* mCurrentDepth;
	Texture* mDeepestDepth;
	ScoreBoard* mScore;
	ScoreBoard* mHighScore;

	// Title entities
	GameEntity* mTitle;
	Texture* mTitle00;
	Texture* mTitle01;
	Texture* mTitle02;
	Texture* mCover;

	// Menu entities
	GameEntity* mMenu;
	Texture* mPlay;
	Texture* mCredits;
	AnimatedTexture* mCursor;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffset;
	int mMenuSelection;

	// Animation variables
	// ================================
	// "Rick Tangle in:" (Position Lerp)
	Vector2 mTitleAnimStartPos;
	Vector2 mTitleAnimEndPos;
	float mTitleAnimTotalTime;
	float mTitleAnimTimer;
	bool mTitleAnimDone;

	// "Basement BREAKIN:" (Modulate Alpha, float Lerp)
	float mAlpha01AnimStartVal;
	float mAlpha01AnimEndVal;
	float mAlpha01AnimTotalTime;
	float mAlpha01AnimTimer;
	bool mAlpha01AnimDone;

	// "Play"/"Credits" (Position Lerp)
	Vector2 mMenu01AnimStartPos;
	Vector2 mMenu01AnimEndPos;
	Vector2 mMenu02AnimStartPos;
	Vector2 mMenu02AnimEndPos;
	float mMenuAnimTotalTime;
	float mMenuAnimTimer;
	bool mMenuAnimDone;

public:
	StartScreen();
	~StartScreen();

	void ResetAnimation();
	int MenuSelection(); // SelectedMode in tutorial

	void ChangeMenuSelection(int change);

	void Update();
	void Render();
};