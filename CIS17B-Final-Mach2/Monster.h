#pragma once
#include "AnimatedTexture.h"
#include "Collider.h";

using namespace QuickSDL;

class Monster :public GameEntity
{
private:
	Timer* mTimer;

	float mSpeedLo;
	float mSpeedHi;
public:

	AnimatedTexture* mTexture;
	float mSpeed;
	Collider* mCollider;

public:

	Monster(float speedLo, float speedHi);
	~Monster();

	// Lerp between enemy's position and player's position
	void Move(Vector2 target);

	void Update();
	void Render();
};