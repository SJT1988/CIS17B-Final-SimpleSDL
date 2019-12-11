#include "Player.h"

Player::Player()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mFlip = SDL_FLIP_NONE;
	mDirection = VEC2_UP;

	mStuck = false;
	mVisible = false;
	mAnimating = false;

	mScore = 0;
	mLives = 1;

	//========================
	// set collider

	mCollider = new Collider(Vector2(24.0f,24.0f), Collider::Player);
	mCollider->Parent(this);
	mCollider->Pos(VEC2_ZERO);

	//========================
	// initialize animations
	AnimatedTexture* mAnim_IdleUp =
		new AnimatedTexture("RickTangle_SpriteSheet.png", 0, TILE_WIDTH * 0, TILE_WIDTH, TILE_WIDTH, 1, 0.0f, AnimatedTexture::horizontal);
	mAnimations.push_back(mAnim_IdleUp);

	AnimatedTexture* mAnim_IdleDown =
		new AnimatedTexture("RickTangle_SpriteSheet.png", 0, TILE_WIDTH * 1, TILE_WIDTH, TILE_WIDTH, 1, 0.0f, AnimatedTexture::horizontal);
	mAnimations.push_back(mAnim_IdleDown);

	AnimatedTexture* mAnim_IdleRight =
		new AnimatedTexture("RickTangle_SpriteSheet.png", 0, TILE_WIDTH * 2, TILE_WIDTH, TILE_WIDTH, 1, 0.0f, AnimatedTexture::horizontal);
	mAnimations.push_back(mAnim_IdleRight);

	AnimatedTexture* mAnim_WalkUp =
		new AnimatedTexture("RickTangle_SpriteSheet.png", 0, TILE_WIDTH * 3, TILE_WIDTH, TILE_WIDTH, 4, 0.5f, AnimatedTexture::horizontal);
	mAnimations.push_back(mAnim_WalkUp);

	AnimatedTexture* mAnim_WalkDown =
		new AnimatedTexture("RickTangle_SpriteSheet.png", 0, TILE_WIDTH * 4, TILE_WIDTH, TILE_WIDTH, 4, 0.5f, AnimatedTexture::horizontal);
	mAnimations.push_back(mAnim_WalkDown);

	AnimatedTexture* mAnim_WalkRight =
		new AnimatedTexture("RickTangle_SpriteSheet.png", 0, TILE_WIDTH * 5, TILE_WIDTH, TILE_WIDTH, 4, 0.5f, AnimatedTexture::horizontal);
	mAnimations.push_back(mAnim_WalkRight);

	AnimatedTexture* mAnim_ShootUp =
		new AnimatedTexture("RickTangle_SpriteSheet.png", 0, TILE_WIDTH * 6, TILE_WIDTH, TILE_WIDTH, 4, 0.35f, AnimatedTexture::horizontal);
	mAnimations.push_back(mAnim_ShootUp);
	//mAnim_ShootUp->WrapMode(mAnim_ShootUp->once);

	AnimatedTexture* mAnim_ShootDown =
		new AnimatedTexture("RickTangle_SpriteSheet.png", 0, TILE_WIDTH * 7, TILE_WIDTH, TILE_WIDTH, 4, 0.35f, AnimatedTexture::horizontal);
	mAnimations.push_back(mAnim_ShootDown);
	//mAnim_ShootDown->WrapMode(mAnim_ShootDown->once);

	AnimatedTexture* mAnim_ShootRight =
		new AnimatedTexture("RickTangle_SpriteSheet.png", 0, TILE_WIDTH * 8, TILE_WIDTH, TILE_WIDTH, 4, 0.35f, AnimatedTexture::horizontal);
	mAnimations.push_back(mAnim_ShootRight);
	//mAnim_ShootRight->WrapMode(mAnim_ShootRight->once);

	//==========================
	// parent animations
	for (AnimatedTexture* anim : mAnimations)
	{
		anim->Parent(this);
		anim->Pos(VEC2_ZERO);
	}

	mMoveSpeed = 160.0f;

	//====================
	// Bullets

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i] = new Bullet();
	}

	//======================
	// Initilize Texture:

	mPlayerTex = mAnimations[0];
}

Player::~Player()
{
	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;

	for (AnimatedTexture* anim : mAnimations)
	{
		delete anim;
		anim = NULL;
	}

	for (Bullet* b : mBullets)
	{
		delete b;
		b = NULL;
	}
}

void Player::HandleMovement()
{
	// std::cout << mDirection << std::endl;

	// =========================
	// Shoot

	if (mInput->KeyDown(SDL_SCANCODE_SPACE))
	{
		if (mDirection == -VEC2_UP ||
			mDirection == Vector2(-sqrt(2) / 2, -sqrt(2) / 2) ||
			mDirection == Vector2(sqrt(2) / 2, -sqrt(2) / 2))
		{
			mPlayerTex = mAnimations[6];
			return;
		}
		else if (mDirection == VEC2_UP ||
			mDirection == Vector2(-sqrt(2) / 2, sqrt(2) / 2) ||
			mDirection == Vector2(sqrt(2) / 2, sqrt(2) / 2))
		{
			mPlayerTex = mAnimations[7];
			return;
		}
		else if (mDirection == -VEC2_RIGHT)
		{
			mPlayerTex = mAnimations[8];
			return;
		}
		else if (mDirection == VEC2_RIGHT)
		{
			mPlayerTex = mAnimations[8];
			return;
		}
	}

	// ===================
	// Diagonal directions

	if ((mInput->KeyDown(SDL_SCANCODE_UP) || mInput->KeyDown(SDL_SCANCODE_W)) &&
		(mInput->KeyDown(SDL_SCANCODE_LEFT) || mInput->KeyDown(SDL_SCANCODE_A)))
	{
		mDirection = Vector2(-sqrt(2) / 2, -sqrt(2) / 2);
		mPlayerTex = mAnimations[3];
		mFlip = SDL_FLIP_NONE;
		Translate(Vector2(-sqrt(2) / 2, -sqrt(2) / 2) * mMoveSpeed*mTimer->DeltaTime());
	}
	else if ((mInput->KeyDown(SDL_SCANCODE_UP) || mInput->KeyDown(SDL_SCANCODE_W)) &&
		(mInput->KeyDown(SDL_SCANCODE_RIGHT) || mInput->KeyDown(SDL_SCANCODE_D)))
	{
		mDirection = Vector2(sqrt(2) / 2, -sqrt(2) / 2);
		mPlayerTex = mAnimations[3];
		mFlip = SDL_FLIP_NONE;
		Translate(Vector2(sqrt(2) / 2, -sqrt(2) / 2) * mMoveSpeed*mTimer->DeltaTime());
	}
	else if ((mInput->KeyDown(SDL_SCANCODE_DOWN) || mInput->KeyDown(SDL_SCANCODE_S)) &&
		(mInput->KeyDown(SDL_SCANCODE_LEFT) || mInput->KeyDown(SDL_SCANCODE_A)))
	{
		mDirection = Vector2(-sqrt(2) / 2, sqrt(2) / 2);
		mPlayerTex = mAnimations[4];
		mFlip = SDL_FLIP_NONE;
		Translate(Vector2(-sqrt(2) / 2, sqrt(2) / 2) * mMoveSpeed*mTimer->DeltaTime());
	}
	else if ((mInput->KeyDown(SDL_SCANCODE_DOWN) || mInput->KeyDown(SDL_SCANCODE_S)) &&
		(mInput->KeyDown(SDL_SCANCODE_RIGHT) || mInput->KeyDown(SDL_SCANCODE_D)))
	{
		mDirection = Vector2(sqrt(2) / 2, sqrt(2) / 2);
		mPlayerTex = mAnimations[4];
		mFlip = SDL_FLIP_NONE;
		Translate(Vector2(sqrt(2) / 2, sqrt(2) / 2) * mMoveSpeed*mTimer->DeltaTime());
	}
	// ===================
	// Cardinal directions
	else if (mInput->KeyDown(SDL_SCANCODE_UP) || mInput->KeyDown(SDL_SCANCODE_W))
	{
		mDirection = -VEC2_UP;
		mPlayerTex = mAnimations[3];
		mFlip = SDL_FLIP_NONE;
		Translate(mDirection * mMoveSpeed*mTimer->DeltaTime());
	}
	else if (mInput->KeyDown(SDL_SCANCODE_DOWN) || mInput->KeyDown(SDL_SCANCODE_S))
	{
		mDirection = VEC2_UP;
		mPlayerTex = mAnimations[4];
		mFlip = SDL_FLIP_NONE;
		Translate(mDirection * mMoveSpeed*mTimer->DeltaTime());
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT) || mInput->KeyDown(SDL_SCANCODE_A))
	{
		mDirection = -VEC2_RIGHT;
		mPlayerTex = mAnimations[5];
		mFlip = SDL_FLIP_HORIZONTAL;
		Translate(mDirection * mMoveSpeed*mTimer->DeltaTime());
	}
	else if (mInput->KeyDown(SDL_SCANCODE_RIGHT) || mInput->KeyDown(SDL_SCANCODE_D))
	{
		mDirection = VEC2_RIGHT;
		mPlayerTex = mAnimations[5];
		mFlip = SDL_FLIP_NONE;
		Translate(mDirection*mMoveSpeed*mTimer->DeltaTime());
	}

	// ==================
	// Idle

	else
	{
		if (mDirection == -VEC2_UP)
		{
			mPlayerTex = mAnimations[0];
			mFlip = SDL_FLIP_NONE;
		}
		else if (mDirection == VEC2_UP)
		{
			mPlayerTex = mAnimations[1];
			mFlip = SDL_FLIP_NONE;
		}
		else if (mDirection == -VEC2_RIGHT)
		{
			mPlayerTex = mAnimations[2];
			mFlip = SDL_FLIP_HORIZONTAL;
		}
		else if (mDirection == VEC2_RIGHT)
		{
			mPlayerTex = mAnimations[2];
			mFlip = SDL_FLIP_NONE;
		}
	}
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
/*
void Player::AddScore(int change)
{
	mScore += change;
}
*/


void Player::Update()
{
	if (Active() && !mStuck)
	{
		HandleMovement();
		mPlayerTex->Update();
	}

	if (mInput->KeyPressed(SDL_SCANCODE_SPACE))
	{
		for (Bullet* b : mBullets)
		{
			if (!(b->Active()))
			{
				//std::cout << Pos() << std::endl;
				//std::cout << this->Pos() << std::endl;
				b->Pos(Pos());
				b->mDirection = this->mDirection;
				b->Fire();
				break;
			}
		}
	}
	for (Bullet* b : mBullets)
	{
		b->Update();
	}
}

void Player::Render()
{
	if (mVisible && Active())
	{
		mPlayerTex->mFlip = Player::mFlip;
		mPlayerTex->Render();
		mCollider->Render();
	}
	for (Bullet* b : mBullets)
	{
		if (b->Active())
			b->Render();
	}
}