#include "StartScreen.h"
#include <iostream>

StartScreen::StartScreen()
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	// mInput = InputManager::Instance();
	// ================================================================
	// Screen Animation variables

	ResetAnimation();

	// ================================================================
	// top bar entities

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

	// ================================================================
	// Title entities

	mTitle = new GameEntity(mTitleAnimStartPos);

	mTitle00 = new Texture("Rick Tangle in:", "forgotmybazookaathome.ttf", 18, { 255,255,255 });
	mTitle01 = new Texture("Basement", "impact.ttf", 48, { 228,0,0,0});
	mTitle02 = new Texture("BREAKIN", "impact.ttf", 72, { 228,0,0,0});
	mCover = new Texture("black.png", 0, 0, 256, 108);
	SDL_SetTextureAlphaMod(mCover->mTex, 255);
	SDL_SetTextureBlendMode(mCover->mTex, SDL_BLENDMODE_BLEND); //possibly pointless

	mTitle00->Parent(mTitle);
	mTitle01->Parent(mTitle);
	mTitle02->Parent(mTitle);
	mCover->Parent(mTitle);

	mTitle00->Pos(Vector2(0, -64));
	mTitle01->Pos(Vector2(0,-24));
	mTitle02->Pos(Vector2(0, 32));
	mCover->Pos(Vector2(0, 10));

	mTitle->Parent(this);

	// ================================================================
	// Menu entities

	mMenu = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f,
		Graphics::Instance()->SCREEN_HEIGHT*0.67f));
	mPlay = new Texture("Play", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	mCredits = new Texture("Credits", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	mCursor = new AnimatedTexture("monster.png", 0.0f, 0.0f, 64, 64, 4, 0.25f, AnimatedTexture::horizontal);

	
	mPlay->Parent(mMenu);
	mCredits->Parent(mMenu);
	mCursor->Parent(mMenu);

	mPlay->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*-0.67, -24.0f));
	mCredits->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.67, 24.0f));
	mCursor->Pos(Vector2(-80.0f, -24.0f));

	mMenu->Parent(this);

	mCursorStartPos = mCursor->Pos(local);
	mCursorOffset = Vector2(-28.0f, 48.0f);
	mMenuSelection = 0;
}

StartScreen::~StartScreen()
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
	delete mTitle;
	mTitle = NULL;
	delete mTitle00;
	mTitle00 = NULL;
	delete mTitle01;
	mTitle01 = NULL;
	delete mTitle02;
	mTitle02 = NULL;
	delete mCover;
	mCover = NULL;

	// Freeing Menu entities
	delete mMenu;
	mMenu = NULL;
	delete mPlay;
	mPlay = NULL;
	delete mCredits;
	mCredits = NULL;
	delete mCursor;
	mCursor = NULL;
}

void StartScreen::ResetAnimation()
{
	// Title Position Lerp
	mTitleAnimStartPos = Vector2(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f,
		Graphics::Instance()->SCREEN_HEIGHT));
	mTitleAnimEndPos = Vector2(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f,
		Graphics::Instance()->SCREEN_HEIGHT*0.4f));
	mTitleAnimTotalTime = 1.5f;
	mTitleAnimTimer = 0.0f;
	mTitleAnimDone = false;

	// Title Color Lerp
	mAlpha01AnimStartVal = 255;
	mAlpha01AnimEndVal = 0;
	mAlpha01AnimTotalTime = 1.0f;
	mAlpha01AnimTimer = 0.0f;
	mAlpha01AnimDone = false;

	// Menu Position Lerp
	mMenu01AnimStartPos = Vector2(Graphics::Instance()->SCREEN_WIDTH*-0.67, -24.0f);
	mMenu01AnimEndPos = Vector2(0.0f, -24.0f);
	mMenu02AnimStartPos = Vector2(Graphics::Instance()->SCREEN_WIDTH*0.67, 24.0f);
	mMenu02AnimEndPos = Vector2(0.0f, 24.0f);
	mMenuAnimTotalTime = 1.5f;
	mMenuAnimTimer = 0.0f;
	mMenuAnimDone = false;
}

int StartScreen::MenuSelection()
{
	return mMenuSelection;
}

void StartScreen::ChangeMenuSelection(int change)
{
	mMenuSelection += change;

	if (mMenuSelection < 0)
	{
		mMenuSelection = 1;
	}
	else if (mMenuSelection > 1)
	{
		mMenuSelection = 0;
	}

	mCursor->Pos(mCursorStartPos + mCursorOffset * mMenuSelection);
	mAudio->PlaySFX("FF7_CursorMove.wav");
}

void StartScreen::Update()
{
	if (!mTitleAnimDone)
	{
		mTitleAnimTimer += mTimer->DeltaTime();
		mTitle->Pos(Lerp(mTitleAnimStartPos, mTitleAnimEndPos, mTitleAnimTimer / mTitleAnimTotalTime));

		if (mTitleAnimTimer >= mTitleAnimTotalTime)
		{
			mTitleAnimDone = true;
		}
	}

	if (mTitleAnimDone && !mAlpha01AnimDone)
	{
		mAlpha01AnimTimer += mTimer->DeltaTime();
		SDL_SetTextureAlphaMod(mCover->mTex, Lerp(mAlpha01AnimStartVal, mAlpha01AnimEndVal, mAlpha01AnimTimer / mAlpha01AnimTotalTime));

		if (mAlpha01AnimTimer >= mAlpha01AnimTotalTime)
		{
			mAlpha01AnimDone = true;
		}
	}

	if (mTitleAnimDone && mAlpha01AnimDone && !mMenuAnimDone)
	{
		mMenuAnimTimer += mTimer->DeltaTime();
		mPlay->Pos(Lerp(mMenu01AnimStartPos, mMenu01AnimEndPos, mMenuAnimTimer / mMenuAnimTotalTime));
		mCredits->Pos(Lerp(mMenu02AnimStartPos, mMenu02AnimEndPos, mMenuAnimTimer / mMenuAnimTotalTime));

		if (mMenuAnimTimer >= mMenuAnimTotalTime)
		{
			mMenuAnimDone = true;
		}
	}
	
	// If all of the animations are done, we can move the cursor:
	if (mTitleAnimDone && mAlpha01AnimDone && mMenuAnimDone)
	{
		/* set the input if it does not already exist (this is what prevents screen from changing
		before all the animations are done)		
		*/
		if (mInput == NULL)
		{
			mInput = InputManager::Instance();
		}
		if (mInput->KeyPressed(SDL_SCANCODE_DOWN) || mInput->KeyPressed(SDL_SCANCODE_S))
			ChangeMenuSelection(1);
		else if (mInput->KeyPressed(SDL_SCANCODE_UP) || mInput->KeyPressed(SDL_SCANCODE_W)) ChangeMenuSelection(-1);
		mCursor->Update();
	}

	
}

void StartScreen::Render()
{
	mCurrentDepth->Render();
	mDeepestDepth->Render();
	mScore->Render();
	mHighScore->Render();

	mTitle00->Render();
	mTitle01->Render();
	mTitle02->Render();
	if (mCover)
	{
		mCover->Render();
	}

	mPlay->Render();
	mCredits->Render();
	
	if (mTitleAnimDone && mAlpha01AnimDone && mMenuAnimDone)
	{
		mCursor->Render();
	}
	
}