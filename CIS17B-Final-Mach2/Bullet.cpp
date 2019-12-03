#include "Bullet.h"

Bullet::Bullet(Vector2 direction)
{
	mTimer = Timer::Instance();
	mTexture = new Texture("bullet.png");
	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);
	mDirection = direction;
}

Bullet::~Bullet()
{
	mTimer = NULL;

	delete mTexture;
	mTexture = NULL;
	delete &mDirection;
	mDirection = NULL;
	delete &mSpeed;
	mSpeed = NULL;
}
/*
void Bullet::Fire()
{
	Pos(local) += mDirection * mSpeed * mTimer->DeltaTime();
}
*/
void Bullet::Update()
{
	Translate(mDirection * mSpeed * mTimer->DeltaTime());
	/*
	if ((Pos(world).x < 0 || Pos(world).x > Graphics::Instance()->SCREEN_WIDTH) ||
		(Pos(world).y < 0 || Pos(world).y > Graphics::Instance()->SCREEN_HEIGHT))
	{
		this->~Bullet();
	}
	Fire();
	*/
}

void Bullet::Render()
{
	mTexture->Render();
}
