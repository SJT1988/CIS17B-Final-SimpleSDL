#include "Bullet.h"
#include "BoxCollider.h"

Bullet::Bullet()
{
	Active(false);
	mTimer = Timer::Instance();
	mTexture = new Texture("bullet.png");
	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);
	mDirection = VEC2_ZERO;

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));
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
	Pos(VEC2_ZERO);
	//mDirection = VEC2_ZERO;
}

void Bullet::Update()
{
	//std::cout << mDirection << std::endl;
	if (Active())
	{
		Translate(mDirection * mSpeed * mTimer->DeltaTime());
		
		//std::cout << Pos(local).x << "," << Pos(local).y << std::endl;
		if ((Pos(world).x < 0 || Pos(world).x > Graphics::Instance()->SCREEN_WIDTH) ||
			(Pos(world).y < 0 || Pos(world).y > Graphics::Instance()->SCREEN_HEIGHT))
		{
			Reload();
		}
	}

}

void Bullet::Render()
{
	if (Active())
	{
		mTexture->Render();
		PhysicsEntity::Render();
	}
}
