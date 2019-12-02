#include "Player.h"

Player::Player()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mVisible = false;
	mAnimating = false;

	mScore = 0;
	mLives = 1;

	mPlayerTex = new AnimatedTexture("RickTangle_SpriteSheet.png", 0, 64, 64, 64,1,0.0f, AnimatedTexture::horizontal);
	mPlayerTex->Parent(this);
	mPlayerTex->Pos(VEC2_ZERO);

	mMoveSpeed = 160.0f;
	// The player's body occupies a 32x32 pixel region, and his reference is his center, so 32/2 = 16
	//provides the correct offset for the bounds.
	mMoveBounds = Vector2(Graphics::Instance()->SCREEN_WIDTH - OFFSET, Graphics::Instance()->SCREEN_HEIGHT - OFFSET);
}

Player::~Player()
{
	mTimer = NULL;
	mInput = NULL;
	delete mPlayerTex;
	mPlayerTex = NULL;
}

void Player::HandleMovement()
{
	if (mInput->KeyDown(SDL_SCANCODE_UP) || mInput->KeyDown(SDL_SCANCODE_W))
	{
	Translate(-VEC2_UP * mMoveSpeed*mTimer->DeltaTime());
	}
	else if (mInput->KeyDown(SDL_SCANCODE_DOWN) || mInput->KeyDown(SDL_SCANCODE_S))
	{
	Translate(VEC2_UP * mMoveSpeed*mTimer->DeltaTime());
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT) || mInput->KeyDown(SDL_SCANCODE_A))
	{
	Translate(-VEC2_RIGHT * mMoveSpeed*mTimer->DeltaTime());
	}
	else if (mInput->KeyDown(SDL_SCANCODE_RIGHT) || mInput->KeyDown(SDL_SCANCODE_D))
	{
		Translate(VEC2_RIGHT*mMoveSpeed*mTimer->DeltaTime());
	}

	Vector2 pos = Pos(local);
	if (pos.x < OFFSET) pos.x = OFFSET;
	else if (pos.x > mMoveBounds.x) pos.x = mMoveBounds.x;
	if (pos.y < OFFSET) pos.y = OFFSET;
	else if (pos.y > mMoveBounds.y) pos.y = mMoveBounds.y;

	Pos(pos);
}

void Player::Visible(bool visible)
{
	mVisible = visible;
}

bool Player::IsAnimating()
{
	return mAnimating;
}

int Player::GetScore()
{
	return mScore;
}

int Player::GetLives()
{
	return mLives;
}

void Player::AddScore(int change)
{
	mScore += change;
}

// oh shit, I am going to have to retrofit this...

void Player::Update()
{
	if (mAnimating)
	{
		// do stuff
	}
	else
	{
		if (Active())
		{
			HandleMovement();
		}
	}
}

void Player::Render()
{
	if (mVisible)
	{
		mPlayerTex->Render();
	}
}
