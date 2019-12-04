#include "Bullet.h"

Bullet::Bullet()
{
	Active(false);
	mTimer = Timer::Instance();
	mTexture = new Texture("bullet.png");
	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);
	mDirection = VEC2_ZERO;
}

Bullet::~Bullet()
{
	mTimer = NULL;

	delete mTexture;
	mTexture = NULL;
	
	
}

void Bullet::Fire()
{
	Active(true);
}


void Bullet::Reload()
{
	Active(false);
	Pos(local) = VEC2_ZERO;
}

void Bullet::Update()
{
	if (Active())
	{
		Translate(mDirection * mSpeed * mTimer->DeltaTime());
		
		if ((Pos(world).x < 0 || Pos(world).x > Graphics::Instance()->SCREEN_WIDTH) ||
			(Pos(world).y < 0 || Pos(world).y > Graphics::Instance()->SCREEN_HEIGHT))
		{
			Reload();
		}
	}

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
	if (Active())
	{
		mTexture->Render();
	}
}
