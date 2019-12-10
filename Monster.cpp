#include "Monster.h"

Monster::Monster(float speedLo, float speedHi)
{
	mTimer = Timer::Instance();
	mSpeedLo = speedLo;
	mSpeedHi = speedHi;

	//mTexture = new AnimatedTexture("collider.png", 0.0f, 0.0f, 32, 32, 1, 1.0f, AnimatedTexture::horizontal);
	mTexture = new AnimatedTexture("monster.png", 0.0f, 0.0f, 64, 64, 4, 0.25f, AnimatedTexture::horizontal);
	mTexture->Parent(this);

	mCollider = new Collider(Vector2(32.0f, 32.0f), Collider::Monster);
	mCollider->Parent(this);
	mCollider->Pos(VEC2_ZERO);
}

Monster::~Monster()
{
	mTimer = NULL;

	delete mTexture;
	mTexture = NULL;
}

void Monster::Move(Vector2 target)
{
	// Direction to travel in:
	Vector2 direction = (target - Pos()).Normalized();
	// Set a random speed in range [mSpeedLo, mSpeedHi]:
	mSpeed = RandomFloat(mSpeedLo, mSpeedHi);
	// Move the monster toward target at speed:
	Translate(direction * mSpeed * mTimer->DeltaTime());
}

void Monster::Update()
{
	if (Active())
		mTexture->Update();
}

void Monster::Render()
{
	if (Active())
	{
		mTexture->Render();
		mCollider->Render();
	}
}