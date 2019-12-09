#pragma once
#include "Texture.h"

using namespace QuickSDL;

class Collider : public GameEntity
{
private:

	static const int MAX_VERTS = 4;
	GameEntity* mVerts[MAX_VERTS];

public:
	enum TriggerType {Bullet, Wall, Web, Spikes, Exit, Player, Monster};
	Vector2 mSize;

protected:

	TriggerType mTrigger;
	static const bool SHOW_COLLIDERS = true;
	Texture* mTexture;

public:

	Collider(Vector2 size,TriggerType type);
	~Collider();

	bool AABB(Collider colA, Collider colB);

	void Render();

private:

	void AddVertex(int index, Vector2 pos);
	void SetTexture(Texture* texture);
	void SetTrigger(TriggerType trigger);
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