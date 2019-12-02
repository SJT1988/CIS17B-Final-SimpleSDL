#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"

using namespace QuickSDL;

class Player :public GameEntity
{
private:
	Timer* mTimer;
	InputManager* mInput;

	bool mVisible;
	bool mAnimating; //used if player is killed

	int mScore;
	int mLives;

	Texture* mPlayerTex;
	float mMoveSpeed;
	Vector2 mMoveBounds;
	const float OFFSET = 16.0f;

private:

	void HandleMovement();

public:

	Player();
	~Player();

	void Visible(bool visible);
	bool IsAnimating();

	int GetScore();
	int GetLives();

	void AddScore(int change);

	void Update();
	void Render();
};