#include "Collider.h"

Collider::Collider(Vector2 size, TriggerType type)
{
	mSize = size;
	mTrigger = type;
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

bool Collider::AABB(Collider* colA, Collider* colB)
{
	//std::cout << "colA.mVerts[0]->Pos()\.x " << colA.mVerts[0]->Pos().x << "+ colA.mSize.x " << colA.mSize.x << "> colB.mVerts[0]->Pos()\.x" << colB.mVerts[0]->Pos().x << "&&" << std::endl;
	//std::cout << "colB.mVerts[0]->Pos()\.x " << colB.mVerts[0]->Pos().x << "+ colB.mSize.x " << colB.mSize.x << "> colA.mVerts[0]->Pos()\.x" << colA.mVerts[0]->Pos().x << "&&" << std::endl;
	//std::cout << "colA.mVerts[0]->Pos()\.y " << colA.mVerts[0]->Pos().y << "+ colA.mSize.x " << colA.mSize.y << "> colB.mVerts[0]->Pos()\.y" << colB.mVerts[0]->Pos().y << "&&" << std::endl;
	//std::cout << "colB.mVerts[0]->Pos()\.y " << colB.mVerts[0]->Pos().y << "+ colB.mSize.x " << colB.mSize.y << "> colA.mVerts[0]->Pos()\.y" << colA.mVerts[0]->Pos().y << "&&" << std::endl;
	if (
		colA->mVerts[0]->Pos().x + colA->mSize.x > colB->mVerts[0]->Pos().x &&
		colB->mVerts[0]->Pos().x + colB->mSize.x > colA->mVerts[0]->Pos().x &&
		colA->mVerts[0]->Pos().y + colA->mSize.y > colB->mVerts[0]->Pos().y &&
		colB->mVerts[0]->Pos().y + colB->mSize.y > colA->mVerts[0]->Pos().y
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