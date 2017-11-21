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

void PhysicsManager::Update(float deltaTime)
{
	// Generate new collision info
	_contacts.clear();

	for (uint32 i = 0; i < _colliders.size(); ++i)
	{
		ColliderComponent *A = _colliders[i];

		for (uint32 j = i + 1; j < _colliders.size(); ++j)
		{
			ColliderComponent *B = _colliders[j];
			if (A->GetRigidbodyComponent()->im == 0 && B->GetRigidbodyComponent()->im == 0)
				continue;
			Manifold m(A, B);
			m.Solve();
			if (m.contact_count)
				_contacts.emplace_back(m);
		}
	}

	// Integrate forces
	for (uint32 i = 0; i < _colliders.size(); ++i)
		IntegrateForces(_colliders[i], deltaTime);

	// Initialize collision
	for (uint32 i = 0; i < _contacts.size(); ++i)
		_contacts[i].Initialize(deltaTime);

	// Solve collisions
	//for (uint32 j = 0; j < m_iterations; ++j)
	for (uint32 i = 0; i < _contacts.size(); ++i)
		_contacts[i].ApplyImpulse();

	// Integrate velocities
	for (uint32 i = 0; i < _colliders.size(); ++i)
		IntegrateVelocity(_colliders[i], deltaTime);

	// Correct positions
	/*for (uint32 i = 0; i < _contacts.size(); ++i)
		_contacts[i].PositionalCorrection();*/

	// Clear all forces
	for (uint32 i = 0; i < _colliders.size(); ++i)
	{
		ColliderComponent *b = _colliders[i];
		b->GetRigidbodyComponent()->force.Set(0, 0);
		b->GetRigidbodyComponent()->torque = 0;
	}
}

void PhysicsManager::IntegrateForces(ColliderComponent * go, float deltaTime)
{
	if (go->GetRigidbodyComponent()->im == 0.0f)
		return;

	go->GetRigidbodyComponent()->velocity += (go->GetRigidbodyComponent()->force * go->GetRigidbodyComponent()->im + gravity) * (deltaTime / 2.0f);
	go->GetRigidbodyComponent()->angularVelocity += go->GetRigidbodyComponent()->torque * go->GetRigidbodyComponent()->iI * (deltaTime / 2.0f);
}

void PhysicsManager::IntegrateVelocity(ColliderComponent * go, float deltaTime)
{
	if (go->GetRigidbodyComponent()->im == 0.0f)
		return;

	go->GetTransformComponent()->SetPosition(go->GetTransformComponent()->GetPosition() + go->GetRigidbodyComponent()->velocity * deltaTime);
	go->GetRigidbodyComponent()->orient += go->GetRigidbodyComponent()->angularVelocity * deltaTime;
	go->GetRigidbodyComponent()->SetOrient(go->GetRigidbodyComponent()->orient);
	go->SetOrient(go->GetRigidbodyComponent()->orient);
	IntegrateForces(go, deltaTime);
}
