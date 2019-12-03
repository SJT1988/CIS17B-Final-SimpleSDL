#pragma once
#include "Texture.h"
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

public:
	Bullet(Vector2 direction);
	~Bullet();
	
	// void Fire();

	void Update();
	void Render();
};
