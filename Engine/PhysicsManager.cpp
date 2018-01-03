#include "PhysicsManager.h"

#include "CollisionMessage.h"

void PhysicsManager::BuildObjectGrid(int levelWidth, int levelHeight)
{
	mObjectGrid = new ObjectGrid(levelWidth + 1, levelHeight + 1 , 100, 100);
}

PhysicsManager::~PhysicsManager()
{
	delete mObjectGrid;
}

void PhysicsManager::AddCollider(GameObject* gameObject, ColliderComponent * collider)
{
	mGameObjects.push_back(gameObject);
	mColliders.push_back(collider);

	// LEFT, TOP, RIGHT, BOTTOM
	Rect r = collider->GetRect();
	int ltrb[4];
	ltrb[0] = r.LeftX;
	ltrb[1] = std::abs(r.TopY);
	ltrb[2] = r.RightX;
	ltrb[3] = std::abs(r.BotY);

	mObjectGrid->insert(ltrb, (int)mColliders.size() - 1);

	Vec2 objectCentre = collider->GetCentre();
	collider->GridSquare = mObjectGrid->cell_index((int)objectCentre.x, (int)std::abs(objectCentre.y));
	collider->SetPreviousRect(r);
}

void PhysicsManager::Update(float deltaTime)
{
	// Generate new collision info
	mContacts.clear();

	for (int i = 0; i < mColliders.size(); i++)
	{
		if (mColliders[i]->GetTransformComponent()->CheckChanged())
		{
			Vec2 objectCentre = mColliders[i]->GetCentre();
			int centreCell = mObjectGrid->cell_index((int)objectCentre.x, (int)std::abs(objectCentre.y));

			if (centreCell != mColliders[i]->GridSquare) // Centre cell has changed
			{
				Rect prevRect = mColliders[i]->GetPreviousRect();
				int ltrb[4];
				ltrb[0] = prevRect.LeftX;
				ltrb[1] = std::abs(prevRect.TopY);
				ltrb[2] = prevRect.RightX;
				ltrb[3] = std::abs(prevRect.BotY);
				mObjectGrid->erase(ltrb, i);

				Rect newRect = mColliders[i]->GetRect();
				ltrb[0] = newRect.LeftX;
				ltrb[1] = std::abs(newRect.TopY);
				ltrb[2] = newRect.RightX;
				ltrb[3] = std::abs(newRect.BotY);
				mObjectGrid->insert(ltrb, i);

				mColliders[i]->GridSquare = centreCell;
				mColliders[i]->SetPreviousRect(newRect);
			}

			mColliders[i]->GetTransformComponent()->SetChanged(false);
		}
	}

	for (int i = 0; i < mColliders.size(); i++)
	{
		ColliderComponent *A = mColliders[i];

		if (!A->GetActive())
			continue;

		// Find the cell_index of the centre point of A
		Rect r = A->GetRect();
		int cell = mObjectGrid->cell_index((int)r.Centre.x, (int)std::abs(r.Centre.y));

		const GridNode* node = mObjectGrid->first(cell); // Get the first grid node in this cell
		while (node) // While node is not null go through every element
		{
			int element = node->element;
			node = mObjectGrid->next(node); // Load the next element for the next loop

			if (element <= i) // If the element in this node has an ID less than 'i' that means that we will have already checked this potential collision earlier in the loop
				continue;

			ColliderComponent *B = mColliders[element];
			if (A->GetRigidbodyComponent()->GetInverseMass() == 0 && B->GetRigidbodyComponent()->GetInverseMass() == 0)
				continue;

			if (!B->GetActive())
				continue;

			Collision collision(A, B);
			collision.Solve();

			if (collision.GetContactCount()) // If there is a collision the number of contacts will be greater than 0
			{
				mContacts.emplace_back(collision);

				CollisionMessage colMsg(mGameObjects[i]);
				mGameObjects[element]->SendMessageToComponents(colMsg);

				CollisionMessage colMsg2(mGameObjects[element]);
				mGameObjects[i]->SendMessageToComponents(colMsg2);
			}
		}
	}

	//// Loop through every collider
	//for (int i = 0; i < mColliders.size(); i++)
	//{
	//	ColliderComponent *A = mColliders[i];

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
	//		ColliderComponent *B = mColliders[objs[j]];

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

	/*for (int i = 0; i < mColliders.size(); ++i)
	{
		ColliderComponent *A = mColliders[i];

		if (!A->GetActive())
			continue;

		for (int j = i + 1; j < mColliders.size(); ++j)
		{
			ColliderComponent *B = mColliders[j];
			if (A->GetRigidbodyComponent()->GetInverseMass() == 0 && B->GetRigidbodyComponent()->GetInverseMass() == 0)
				continue;

			if (!B->GetActive())
				continue;

			Collision collision(A, B);
			collision.Solve();

			if (collision.GetContactCount())
			{
				mContacts.emplace_back(collision);

				CollisionMessage colMsg(mGameObjects[i]);
				mGameObjects[j]->SendMessageToComponents(colMsg);

				CollisionMessage colMsg2(mGameObjects[j]);
				mGameObjects[i]->SendMessageToComponents(colMsg2);
			}
		}
	}*/

	// Integrate forces
	for (int i = 0; i < mColliders.size(); ++i)
		IntegrateForces(mColliders[i], deltaTime);

	// Initialize collision
	for (int i = 0; i < mContacts.size(); ++i)
		mContacts[i].Initialize(deltaTime);
		
	// Solve collisions
	for (int i = 0; i < mContacts.size(); ++i)
		mContacts[i].ApplyImpulse();

	// Integrate velocities
	for (int i = 0; i < mColliders.size(); ++i)
		IntegrateVelocity(mColliders[i], deltaTime);

	// Correct positions
	for (int i = 0; i < mContacts.size(); ++i)
		mContacts[i].PositionalCorrection();

	// Clear all forces
	for (int i = 0; i < mColliders.size(); ++i)
	{
		ColliderComponent *b = mColliders[i];
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
		(GRAVITY_VECTOR * (collider->GetRigidbodyComponent()->GetInverseMass() * 3000))) * (deltaTime / 2.0f));

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
