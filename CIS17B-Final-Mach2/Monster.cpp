#include "Monster.h"

Monster::Monster(float speedLo, float speedHi)
{
	mTimer = Timer::Instance();
	mSpeed = RandomFloat(speedLo, speedHi);

	//mTexture = new AnimatedTexture("collider.png", 0.0f, 0.0f, 32, 32, 1, 1.0f, AnimatedTexture::horizontal);
	mTexture = new AnimatedTexture("monster.png", 0.0f, 0.0f, 64, 64, 4, 0.25f, AnimatedTexture::horizontal);
	mTexture->Parent(this);
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
	// Move the monster toward target at speed:
	Translate(direction * mSpeed * mTimer->DeltaTime());
}

void Monster::Update()
{
	mTexture->Update();
}

void Monster::Render()
{
	mTexture->Render();
}
