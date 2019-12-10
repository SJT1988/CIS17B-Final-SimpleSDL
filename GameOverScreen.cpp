#include "GameOverScreen.h"

#include <iostream>

GameOverScreen::GameOverScreen()
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	// mInput = InputManager::Instance();
	// ================================================================

	// ================================================================
	// top bar entities

	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 32.0f));
	mCurrentDepth = new Texture("DEPTH:", "forgotmybazookaathome.ttf", 24, { 228,0,0 });
	mDeepestDepth = new Texture("HI-SCORE:", "forgotmybazookaathome.ttf", 24, { 228,0,0 });
	mScore = new ScoreBoard({ 255,255,255 }); // mCurrentDepth <-> mScore
	mHighScore = new ScoreBoard({ 255,255,255 }); // mDeepestDepth <-> mHighScore

	mCurrentDepth->Parent(mTopBar);
	mDeepestDepth->Parent(mTopBar);
	mScore->Parent(mTopBar);
	mHighScore->Parent(mTopBar);

	mDeepestDepth->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * -0.4f, 0.0f));
	mCurrentDepth->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.25f - 48.0f, 0.0f));
	mScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.425f, 0.0f));
	mHighScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * -0.2f + 32.0f, 0.0f));
	mTopBar->Parent(this);

	// ================================================================
	// Title entities

	mGameOver = new Texture("YOU DIED", "impact.ttf", 256, { 228,0,0,0 });
	mGameOver->Parent(this);
	mGameOver->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	// ================================================================
}

GameOverScreen::~GameOverScreen()
{
	// Freeing topBar entities
	delete mTopBar;
	mTopBar = NULL;
	delete mCurrentDepth;
	mCurrentDepth = NULL;
	delete mDeepestDepth;
	mDeepestDepth = NULL;
	delete mScore;
	mScore = NULL;
	delete mHighScore;
	mHighScore = NULL;

	// Freeing title entities
	delete mGameOver;
	mGameOver = NULL;
}

void GameOverScreen::Update()
{
}

void GameOverScreen::Render()
{
	mCurrentDepth->Render();
	mDeepestDepth->Render();
	mScore->Render();
	mHighScore->Render();
	mGameOver->Render();
}