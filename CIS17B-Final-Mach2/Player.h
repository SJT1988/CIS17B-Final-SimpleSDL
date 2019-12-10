#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Bullet.h"
#include <vector>

using namespace QuickSDL;

class Player :public GameEntity
{
public:
	bool mStuck;
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;
	SDL_Renderer* mRenderer;

	std::vector<AnimatedTexture*> mAnimations;
	SDL_RendererFlip mFlip;

	const int TILE_WIDTH = 64;

	Vector2 mDirection;
	bool mVisible;
	bool mAnimating; //used if player is killed

	int mScore;
	int mLives;

	AnimatedTexture* mPlayerTex;

	float mMoveSpeed;

	// moved next 2 lines to PlayScreen.h:
	// Vector2 mMoveBounds;
	// const float OFFSET = 16.0f;

	

	//==================
	// Bullet

	const static int MAX_BULLETS = 4;
	Bullet* mBullets[MAX_BULLETS];

public:

	Collider* mCollider;

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
	//void WasHit();

	void Update();
	void Render();
};