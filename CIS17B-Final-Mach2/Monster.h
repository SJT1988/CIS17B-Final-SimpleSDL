#pragma once
#include "AnimatedTexture.h"

using namespace QuickSDL;

class Monster:public GameEntity
{
private:
	Timer* mTimer;
public:

	AnimatedTexture* mTexture;
	float mSpeed;
	
public:

	Monster(float speedLo, float speedHi);
	~Monster();

	// Lerp between enemy's position and player's position
	void Move(Vector2 target);

	void Update();
	void Render();
};