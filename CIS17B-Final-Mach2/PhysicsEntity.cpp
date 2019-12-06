#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity()
{

}

PhysicsEntity::~PhysicsEntity()
{
	for (Collider* c : mColliders)
	{
		delete c;
		c = nullptr;
	}

	mColliders.clear();
}

void PhysicsEntity::AddCollider(Collider* collider, Vector2 localPos)
{
	collider->Parent(this);
	collider->Pos(localPos);
	mColliders.push_back(collider);
}

void PhysicsEntity::Render()
{
	for (Collider* c : mColliders)
	{
		c->Render();
	}
}