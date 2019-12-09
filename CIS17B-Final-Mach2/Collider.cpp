#include "Collider.h"

Collider::Collider(Vector2 size, TriggerType type)
{
	mSize = size;
	// Left-Right, Top-Bottom order
	AddVertex(0, Vector2(-0.5f*size.x, -0.5f*size.y));
	AddVertex(1, Vector2(0.5f*size.x, -0.5f*size.y));
	AddVertex(2, Vector2(-0.5f*size.x, 0.5f*size.y));
	AddVertex(3, Vector2(0.5f*size.x, 0.5f*size.y));

	mTexture = nullptr;

	if (SHOW_COLLIDERS)
	{
		if (mTrigger == Web)
			SetTexture(new Texture("collider2.png"));
		else if (mTrigger == Spikes)
			SetTexture(new Texture("collider3.png"));
		else if (mTrigger == Exit)
			SetTexture(new Texture("exit.png"));
		else // Bullet, Wall, or other
			SetTexture(new Texture("collider.png"));
		// this outta do it:
		mTexture->Scale(this->mSize / mTexture->mWidth);

		//this part made no sense:
		//mTexture->Scale(size / 100.0f);
	}
}

Collider::~Collider()
{
	if (mTexture)
	{
		delete mTexture;
		mTexture = nullptr;
	}
}

void Collider::AddVertex(int index, Vector2 pos)
{
	mVerts[index] = new GameEntity(pos);
	mVerts[index]->Parent(this);
}

void Collider::SetTexture(Texture* texture)
{
	delete mTexture;
	mTexture = texture;
	mTexture->Parent(this);
}

void Collider::SetTrigger(TriggerType trigger)
{
	mTrigger = trigger;
}

bool Collider::AABB(Collider colA, Collider colB)
{
	if (
		colA.mVerts[0]->Pos().x + colA.mSize.x >= colB.mVerts[0]->Pos().x &&
		colB.mVerts[0]->Pos().x + colB.mSize.x >= colA.mVerts[0]->Pos().x &&
		colA.mVerts[0]->Pos().y + colA.mSize.y >= colB.mVerts[0]->Pos().y &&
		colB.mVerts[0]->Pos().y + colB.mSize.y >= colA.mVerts[0]->Pos().y
		)
		return true;

	return false;
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