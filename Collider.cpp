#include "Collider.h"

Collider::Collider(ColliderType type) : mType(type)
{
	mTexture = nullptr;
}

Collider::~Collider()
{
	if (mTexture)
	{
		delete mTexture;
		mTexture = nullptr;
	}
}

void Collider::SetTexture(Texture* texture)
{
	delete mTexture;
	mTexture = texture;
	mTexture->Parent(this);
}

void Collider::Render()
{
	if (SHOW_COLLIDERS)
	{
		mTexture->Render();
	}
}
/*
Collider::Collider(SDL_Rect rect)
{
	mCollider = rect;
	mTexture = new Texture("collider.png", mCollider.x, mCollider.y, mCollider.w, mCollider.h);
	mVisible = false;
}

Collider::Collider(float posX, float posY, float width, float height)
{
	mCollider.x = posX;
	mCollider.y = posY;
	mCollider.w = width;
	mCollider.h = height;
	mTexture = new Texture("collider.png", mCollider.x, mCollider.y, mCollider.w, mCollider.h);
	mVisible = false;
}

Collider::~Collider()
{
	delete mTexture;
	mTexture = NULL;
}

bool Collider::AABB(const SDL_Rect rectA, const SDL_Rect rectB)
{
	if (
		rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y
		)
	{
		return true;
	}

	return false;
}

bool Collider::AABB(Collider colliderA, Collider colliderB)
{
	if (AABB(colliderA.mCollider, colliderB.mCollider))
		return true;
	return false;
}

void Collider::SetVisible(bool visible)
{
	mVisible = visible;
}

void Collider::Update()
{	
}

void Collider::Render()
{
	if (this->Active())
		mTexture->Render();
}
*/