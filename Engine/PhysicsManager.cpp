#include "PhysicsManager.h"

#include "CollisionMessage.h"

PhysicsManager::PhysicsManager()
{
	_objectGrid = new ObjectGrid(SCREEN_WIDTH, SCREEN_HEIGHT, 50, 50);
}

PhysicsManager::~PhysicsManager()
{
	delete _objectGrid;
}

void PhysicsManager::AddCollider(GameObject* gameObject, ColliderComponent * collider)
{
	_gameObjects.push_back(gameObject);
	_colliders.push_back(collider);

	// LEFT, TOP, RIGHT, BOTTOM
	int ltrb[4];
	ltrb[0] = (int)collider->GetTransformComponent()->GetPosition().x;
	ltrb[1] = (int)collider->GetTransformComponent()->GetPosition().y;
	ltrb[2] = (int)collider->GetTransformComponent()->GetPosition().x + 100;
	ltrb[3] = (int)collider->GetTransformComponent()->GetPosition().y + 100;

	//_objectGrid->insert(ltrb, _colliders.size() - 1);
}

void PhysicsManager::Update(float deltaTime)
{
	// Generate new collision info
	_contacts.clear();

	Bounds r;
	r.width = 100;
	r.height = 100;

	//for (int i = 0; i < _colliders.size(); i++)
	//{
	//	ColliderComponent *A = _colliders[i];

	//	if (!A->GetActive())
	//		continue;

	//	// Find the cell_index of the centre point of 
	//	_objectGrid->cell_index((int)A->GetTransformComponent()->GetPosition().x, (int)A->GetTransformComponent()->GetPosition().y);
	//}

	//// Loop through every collider
	//for (int i = 0; i < _colliders.size(); i++)
	//{
	//	ColliderComponent *A = _colliders[i];

	//	if (!A->GetActive())
	//		continue;

	//	r.xPos = (int)A->GetTransformComponent()->GetPosition().x;
	//	r.yPos = (int)A->GetTransformComponent()->GetPosition().y;

	//	objs.clear();

	//	// Retrieve any objects around the collider A
	//	_quadTree->Retrieve(objs, r);

	//	// For all objects around the collider A, check if there's an actual intersection
	//	for (int j = 0; j < objs.size(); j++)
	//	{
	//		ColliderComponent *B = _colliders[objs[j]];

	//		if (!B->GetActive())
	//			continue;

	//		if (A->GetRigidbodyComponent()->GetInverseMass() == 0 && B->GetRigidbodyComponent()->GetInverseMass() == 0)
	//			continue;

	//		Collision collision(A, B);
	//		collision.Solve();

	//		if (collision.GetContactCount())
	//		{
	//			_contacts.emplace_back(collision);

	//			CollisionMessage colMsg(_gameObjects[i]);
	//			_gameObjects[objs[j]]->SendMessageToComponents(colMsg);

	//			CollisionMessage colMsg2(_gameObjects[objs[j]]);
	//			_gameObjects[i]->SendMessageToComponents(colMsg2);
	//		}
	//	}
	//}

	for (int i = 0; i < _colliders.size(); ++i)
	{
		ColliderComponent *A = _colliders[i];

		if (!A->GetActive())
			continue;

		for (int j = i + 1; j < _colliders.size(); ++j)
		{
			ColliderComponent *B = _colliders[j];
			if (A->GetRigidbodyComponent()->GetInverseMass() == 0 && B->GetRigidbodyComponent()->GetInverseMass() == 0)
				continue;

			if (!B->GetActive())
				continue;

			Collision collision(A, B);
			collision.Solve();

			if (collision.GetContactCount())
			{
				_contacts.emplace_back(collision);

				CollisionMessage colMsg(_gameObjects[i]);
				_gameObjects[j]->SendMessageToComponents(colMsg);

				CollisionMessage colMsg2(_gameObjects[j]);
				_gameObjects[i]->SendMessageToComponents(colMsg2);
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
	if (collider->GetRigidbodyComponent()->GetInverseMass() == 0.0f || !collider->GetActive())
		return;

	collider->GetRigidbodyComponent()->SetVelocity(collider->GetRigidbodyComponent()->GetVelocity() + 
		(collider->GetRigidbodyComponent()->GetForce() * collider->GetRigidbodyComponent()->GetInverseMass() + 
		(gravity * (collider->GetRigidbodyComponent()->GetInverseMass() * 3000))) * (deltaTime / 2.0f));

	collider->GetRigidbodyComponent()->SetAngularVelocity(collider->GetRigidbodyComponent()->GetAngularVelocity() +
		collider->GetRigidbodyComponent()->GetTorque() * collider->GetRigidbodyComponent()->GetInverseIntertia() * (deltaTime / 2.0f));
}

void PhysicsManager::IntegrateVelocity(ColliderComponent * collider, float deltaTime)
{
	if (collider->GetRigidbodyComponent()->GetInverseMass() == 0.0f || !collider->GetActive())
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
