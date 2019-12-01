#include "HUD.h"

HUD::HUD()
{
	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, 32.0f));
	mCurrentDepth = new Texture("DEPTH:", "forgotmybazookaathome.ttf", 24, { 228,0,0 });
	mDeepestDepth = new Texture("HI-SCORE:", "forgotmybazookaathome.ttf", 24, { 228,0,0 });
	mScore = new ScoreBoard({ 255,255,255 }); // mCurrentDepth <-> mScore
	mHighScore = new ScoreBoard({ 255,255,255 }); // mDeepestDepth <-> mHighScore

	mCurrentDepth->Parent(mTopBar);
	mDeepestDepth->Parent(mTopBar);
	mScore->Parent(mTopBar);
	mHighScore->Parent(mTopBar);

	mDeepestDepth->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*-0.4f, 0.0f));
	mCurrentDepth->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.25f - 48.0f, 0.0f));
	mScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.425f, 0.0f));
	mHighScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*-0.2f + 32.0f, 0.0f));
	mTopBar->Parent(this);
}

HUD::~HUD()
{
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
}

void HUD::SetCurrentScore(int score)
{
	mScore->Score(score);
}

void HUD::SetHighScore(int score)
{
	mHighScore->Score(score);
}

void HUD::Update()
{

}

void HUD::Render()
{
	mTopBar->Render();
	mCurrentDepth->Render();
	mDeepestDepth->Render();
	mScore->Render();
	mHighScore->Render();
}
