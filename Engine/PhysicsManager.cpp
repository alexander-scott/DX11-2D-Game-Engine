#include "PhysicsManager.h"



PhysicsManager::PhysicsManager()
{
}


PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::AddCollider(ColliderComponent * go)
{
	_colliders.push_back(go);
}

void PhysicsManager::Update()
{
	// Generate new collision info
	_contacts.clear();

	for (uint32 i = 0; i < _colliders.size(); ++i)
	{
		ColliderComponent *A = _colliders[i];

		for (uint32 j = i + 1; j < _colliders.size(); ++j)
		{
			ColliderComponent *B = _colliders[j];
			if (A->GetRigidbodyComponent()->im == 0 && A->GetRigidbodyComponent()->im == 0)
				continue;
			Manifold m(A, B);
			m.Solve();
			if (m.contact_count)
				_contacts.emplace_back(m);
		}
	}
}
