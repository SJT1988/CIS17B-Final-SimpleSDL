#pragma once
#include <vector>
#include "Collider.h"

class PhysicsEntity : public GameEntity
{
protected:
	
	std::vector<Collider*> mColliders;

public:

	PhysicsEntity();
	virtual ~PhysicsEntity();

	virtual void Render();

protected:

	void AddCollider(Collider* collider, Vector2 localPos = VEC2_ZERO);
};
