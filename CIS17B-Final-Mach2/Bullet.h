#pragma once
#include "Collider.h"
#include "Timer.h"

using namespace QuickSDL;

class Bullet : public GameEntity
{
private:
	Timer* mTimer;
	Texture* mTexture;
	int mSpeed = 400;

public:
	Vector2 mDirection;
	Collider* mCollider;
public:
	Bullet();
	~Bullet();

	void Fire();
	void Reload();
	void ResolveBulletCollision();

	void Update();
	void Render();
};