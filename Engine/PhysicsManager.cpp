#include "PhysicsManager.h"

#include "CollisionMessage.h"

void PhysicsManager::BuildObjectGrid(int levelWidth, int levelHeight)
{
	mObjectGrid = new ObjectGrid(levelWidth + 1, levelHeight + 1 , 100, 100); // Initalise an object grid with cell size 100,100
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
	collider->CentreGridSquare = mObjectGrid->cell_index((int)r.Centre.x, (int)std::abs(r.Centre.y));
	collider->LeftGridSquare = mObjectGrid->cell_index((int)r.LeftX, (int)std::abs(r.Centre.y));
	collider->RightGridSquare = mObjectGrid->cell_index((int)r.RightX, (int)std::abs(r.Centre.y));
	collider->BottomGridSquare = mObjectGrid->cell_index((int)r.Centre.x, (int)std::abs(r.BotY));
	collider->TopGridSquare = mObjectGrid->cell_index((int)r.Centre.x, (int)std::abs(r.TopY));
	collider->SetPreviousRect(r);
}

void PhysicsManager::Update(float deltaTime)
{
	// Generate new collision info
	mContacts.clear();

	for (int i = 0; i < mColliders.size(); i++)
	{
		// If an objects position has changed it's grid positions might have too so we'll need to update it in the grid
		if (mColliders[i]->GetActive() && mColliders[i]->GetTransformComponent()->CheckChanged())
		{
			UpdateObjectInGrid(mColliders[i], i);
		}
	}

	// Holds a set of every cell index that the collider intersects with. Set is used instead of vector to prevent duplicate cells being inserted
	std::set<int> intersectingCells; 

	for (int i = 0; i < mColliders.size(); i++) // For every collider in the scene
	{
		ColliderComponent *A = mColliders[i];

		if (!A->GetActive()) // Collider must be active
			continue;

		GetIntersectingCells(intersectingCells, A);

		for (auto& cell : intersectingCells) // For each cell that this collider intersects
		{
			const GridNode* node = mObjectGrid->first(cell); // Get the first grid node in this cell

			while (node) // While node is not null go through every collider in the node
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
				collision.CheckForCollision();

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
	}

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
			collision.CheckCollision();

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
		mContacts[i].PrepareToSolve(deltaTime);
		
	// Resolve collisions
	for (int i = 0; i < mContacts.size(); ++i)
		mContacts[i].ResolveCollision();

	// Integrate velocities
	for (int i = 0; i < mColliders.size(); ++i)
		IntegrateVelocity(mColliders[i], deltaTime);

	// Correct positions
	for (int i = 0; i < mContacts.size(); ++i)
		mContacts[i].PenetrationCorrection();

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

void PhysicsManager::UpdateObjectInGrid(ColliderComponent * collider, int colliderIndex)
{
	Rect newRect = collider->GetRect();
	int centreCell = mObjectGrid->cell_index((int)newRect.Centre.x, (int)std::abs(newRect.Centre.y));
	int leftCell = mObjectGrid->cell_index((int)newRect.LeftX, (int)std::abs(newRect.Centre.y));
	int rightCell = mObjectGrid->cell_index((int)newRect.RightX, (int)std::abs(newRect.Centre.y));
	int bottomCell = mObjectGrid->cell_index((int)newRect.Centre.x, (int)std::abs(newRect.BotY));
	int topCell = mObjectGrid->cell_index((int)newRect.Centre.x, (int)std::abs(newRect.TopY));

	if (centreCell != collider->CentreGridSquare ||
		leftCell != collider->LeftGridSquare ||
		rightCell != collider->RightGridSquare ||
		bottomCell != collider->BottomGridSquare ||
		topCell != collider->TopGridSquare) // Cell has changed
	{
		Rect prevRect = collider->GetPreviousRect();
		int ltrb[4];
		ltrb[0] = prevRect.LeftX;
		ltrb[1] = std::abs(prevRect.TopY);
		ltrb[2] = prevRect.RightX;
		ltrb[3] = std::abs(prevRect.BotY);
		mObjectGrid->erase(ltrb, colliderIndex);

		ltrb[0] = newRect.LeftX;
		ltrb[1] = std::abs(newRect.TopY);
		ltrb[2] = newRect.RightX;
		ltrb[3] = std::abs(newRect.BotY);
		mObjectGrid->insert(ltrb, colliderIndex);

		collider->CentreGridSquare = centreCell;
		collider->LeftGridSquare = leftCell;
		collider->RightGridSquare = rightCell;
		collider->BottomGridSquare = bottomCell;
		collider->TopGridSquare = topCell;

		collider->SetPreviousRect(newRect);
	}

	collider->GetTransformComponent()->SetChanged(false);
}

void PhysicsManager::GetIntersectingCells(std::set<int>& intersectingCells, ColliderComponent* collider)
{
	Rect r = collider->GetRect(); // Get the rect belonging to this collider

	intersectingCells.clear();
	for (int i = 0; i < 5; i++) // For every important point on the rect, get the cell that it is in
	{
		if (i == 0) // Centre
			intersectingCells.insert(mObjectGrid->cell_index((int)r.Centre.x, (int)std::abs(r.Centre.y)));
		else if (i == 1) // Left
			intersectingCells.insert(mObjectGrid->cell_index((int)r.LeftX, (int)std::abs(r.Centre.y)));
		else if (i == 2) // Right
			intersectingCells.insert(mObjectGrid->cell_index((int)r.RightX, (int)std::abs(r.Centre.y)));
		else if (i == 3) // Top
			intersectingCells.insert(mObjectGrid->cell_index((int)r.Centre.x, (int)std::abs(r.TopY)));
		else if (i == 4) // Bottom
			intersectingCells.insert(mObjectGrid->cell_index((int)r.Centre.x, (int)std::abs(r.BotY)));
	}
}
