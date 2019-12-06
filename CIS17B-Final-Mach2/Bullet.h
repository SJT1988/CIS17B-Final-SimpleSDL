#pragma once
#include "PhysicsEntity.h"
#include "Timer.h"

using namespace QuickSDL;

class Bullet : public PhysicsEntity
{
private:
	Timer* mTimer;
	Texture* mTexture;
	int mSpeed = 400;

public:
	Vector2 mDirection;

public:
	Bullet();
	~Bullet();
	
	void Fire();
	void Reload();

	void Update();
	void Render();
};
