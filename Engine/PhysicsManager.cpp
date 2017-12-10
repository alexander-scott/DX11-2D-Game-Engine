#include "PhysicsManager.h"

#include "CollisionMessage.h"

PhysicsManager::PhysicsManager()
{
}


PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::AddCollider(GameObject* gameObject, ColliderComponent * collider)
{
	_gameObjects.push_back(gameObject);
	_colliders.push_back(collider);
}

void PhysicsManager::Update(float deltaTime)
{
	// Generate new collision info
	_contacts.clear();

	for (int i = 0; i < _colliders.size(); ++i)
	{
		ColliderComponent *A = _colliders[i];

		for (int j = i + 1; j < _colliders.size(); ++j)
		{
			ColliderComponent *B = _colliders[j];
			if (A->GetRigidbodyComponent()->GetInverseMass() == 0 && B->GetRigidbodyComponent()->GetInverseMass() == 0)
				continue;

			Manifold manifold(A, B);
			manifold.Solve();

			if (manifold.GetContactCount())
			{
				_contacts.emplace_back(manifold);

				CollisionMessage colMsg(_gameObjects[i]);
				_gameObjects[j]->SendMessageToComponents(colMsg);
			}				
		}
	}

	// Integrate forces
	for (int i = 0; i < _colliders.size(); ++i)
		IntegrateForces(_colliders[i], deltaTime);

	// Initialize collision
	for (int i = 0; i < _contacts.size(); ++i)
		_contacts[i].Initialize(deltaTime);
		
	// Solve collisions
	for (int i = 0; i < _contacts.size(); ++i)
		_contacts[i].ApplyImpulse();

	// Integrate velocities
	for (int i = 0; i < _colliders.size(); ++i)
		IntegrateVelocity(_colliders[i], deltaTime);

	// Correct positions
	for (int i = 0; i < _contacts.size(); ++i)
		_contacts[i].PositionalCorrection();

	// Clear all forces
	for (int i = 0; i < _colliders.size(); ++i)
	{
		ColliderComponent *b = _colliders[i];
		b->GetRigidbodyComponent()->SetForce(Vec2(0, 0));
		b->GetRigidbodyComponent()->SetTorque(0);
	}
}

void PhysicsManager::IntegrateForces(ColliderComponent * collider, float deltaTime)
{
	if (collider->GetRigidbodyComponent()->GetInverseMass() == 0.0f)
		return;

	collider->GetRigidbodyComponent()->SetVelocity(collider->GetRigidbodyComponent()->GetVelocity() + 
		(collider->GetRigidbodyComponent()->GetForce() * collider->GetRigidbodyComponent()->GetInverseMass() + 
		(gravity * (collider->GetRigidbodyComponent()->GetInverseMass() * 3000))) * (deltaTime / 2.0f));

	collider->GetRigidbodyComponent()->SetAngularVelocity(collider->GetRigidbodyComponent()->GetAngularVelocity() +
		collider->GetRigidbodyComponent()->GetTorque() * collider->GetRigidbodyComponent()->GetInverseIntertia() * (deltaTime / 2.0f));
}

void PhysicsManager::IntegrateVelocity(ColliderComponent * collider, float deltaTime)
{
	if (collider->GetRigidbodyComponent()->GetInverseMass() == 0.0f)
		return;

	// Calculate position
	collider->GetTransformComponent()->SetPosition(collider->GetTransformComponent()->GetPosition() + collider->GetRigidbodyComponent()->GetVelocity() * deltaTime);

	if (!collider->GetRigidbodyComponent()->RotationLocked())
	{
		// Calculate rotation (RADIANS)
		collider->GetTransformComponent()->SetRotation(collider->GetTransformComponent()->GetRotation()
			+ collider->GetRigidbodyComponent()->GetAngularVelocity() * deltaTime);

		// Set RB orientation matrix
		collider->GetRigidbodyComponent()->SetOrientationMatrix(collider->GetTransformComponent()->GetRotation());
	}
	
	IntegrateForces(collider, deltaTime);
}
