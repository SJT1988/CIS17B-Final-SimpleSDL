#pragma once
#include "Texture.h"

using namespace QuickSDL;

class Collider : public GameEntity
{
private:

	static const int MAX_VERTS = 4;

public:

	enum TriggerType {Bullet, Wall, Web, Spikes, Exit, Player, Monster};
	Vector2 mSize;
	GameEntity* mVerts[MAX_VERTS];

protected:

	TriggerType mTrigger;
	static const bool SHOW_COLLIDERS = true;
	Texture* mTexture;

public:

	Collider(Vector2 size,TriggerType type);
	~Collider();

	static bool AABB(Collider* colA, Collider* colB);

	void Render();

private:

	void AddVertex(int index, Vector2 pos);
	void SetTexture(Texture* texture);
	void SetTrigger(TriggerType trigger);
};