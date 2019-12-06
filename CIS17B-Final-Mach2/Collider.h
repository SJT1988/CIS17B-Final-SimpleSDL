#pragma once
#include "Texture.h"

using namespace QuickSDL;

class Collider : public GameEntity
{
public:
	enum class ColliderType {Box, Circle};

protected:

	ColliderType mType;

	static const bool SHOW_COLLIDERS = true;
	Texture* mTexture;

public:

	Collider(ColliderType type);
	virtual ~Collider();

	virtual void Render();

protected:

	void SetTexture(Texture* texture);
};

/*
class Collider : public GameEntity
{
public:

	SDL_Rect mCollider;
	Texture* mTexture;
	bool mVisible;

public:

	Collider();
	Collider(SDL_Rect rect);
	Collider(float posX, float posY, float width, float height);
	~Collider();
	
	static bool AABB(const SDL_Rect rectA, const SDL_Rect rectB);
	static bool AABB(Collider colliderA, Collider colliderB);
	// Set collider "visible" (true) or "invisible" (false);
	void SetVisible(bool visible);

	void Update();
	void Render();
	
};
*/