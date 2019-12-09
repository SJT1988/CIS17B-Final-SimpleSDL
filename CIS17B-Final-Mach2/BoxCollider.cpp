#include "BoxCollider.h"

BoxCollider::BoxCollider(Vector2 size) : Collider(ColliderType::Box)
{
	// Left-Right, Top-Bottom order
	AddVertex(0, Vector2(-0.5f*size.x, -0.5f*size.y));
	AddVertex(1, Vector2(0.5f*size.x, -0.5f*size.y));
	AddVertex(2, Vector2(-0.5f*size.x, 0.5f*size.y));
	AddVertex(3, Vector2(0.5f*size.x, 0.5f*size.y));

	if (SHOW_COLLIDERS)
	{
		if (mTrigger == Collider::Web)
			Collider::SetTexture(new Texture("collider2.png"));
		else if (mTrigger == Collider::Spikes)
			Collider::SetTexture(new Texture("collider3.png"));
		else if (mTrigger == Collider::Exit)
			Collider::SetTexture(new Texture("exit.png"));
		else
			Collider::SetTexture(new Texture("collider.png"));
		//mTexture->Scale(size / 100.0f);
	}
}

BoxCollider::~BoxCollider()
{
	for (GameEntity* v : mVerts)
	{
		v = nullptr;
	}
}

void BoxCollider::AddVertex(int index, Vector2 pos)
{
	mVerts[index] = new GameEntity(pos);
	mVerts[index]->Parent(this);
}
