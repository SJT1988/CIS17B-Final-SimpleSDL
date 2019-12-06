#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Bullet.h"
#include <vector>
#include "Collider.h"

using namespace QuickSDL;

class Player :public GameEntity
{
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
	Vector2 mMoveBounds;
	const float OFFSET = 16.0f;

	//=================
	// Collider

	

	//==================
	// Bullet

	const static int MAX_BULLETS = 4;
	Bullet* mBullets[MAX_BULLETS];
	// std::vector<Bullet*> mBullets;

	

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
	void WasHit();

	void Update();
	void Render();
};