#pragma once

#include "ColliderComponent.h"
#include "CircleColliderComponent.h"
#include "PolygonColliderComponent.h"

class Collision
{
public:
	Collision(ColliderComponent* a, ColliderComponent* b) : colliderA(a), colliderB(b) { }
	~Collision();

	void CircletoCircle();
	void CircleToPolygon();
	void PolygonToCircle();
	void PolygonToPolygon();

	float FindAxisLeastPenetration(int *faceIndex, PolygonColliderComponent *A, PolygonColliderComponent *B);
	void FindIncidentFace(Vec2 *v, PolygonColliderComponent *RefPoly, PolygonColliderComponent *IncPoly, int referenceIndex);
	int Clip(Vec2 n, float c, Vec2 *face);
	int GetContactCount() { return mContactCount; }

	void Solve();						// Generate contact information
	void Initialize(float deltaTime);   // Precalculations for impulse solving
	void ApplyImpulse();				// Solve impulse and apply
	void PositionalCorrection();		// Naive correction of positional penetration
	void InfiniteMassCorrection();

private:
	ColliderComponent* colliderA;
	ColliderComponent* colliderB;

	float					mPenetration;			 // Depth of penetration from collision
	Vec2					mNormal;				 // From A to B
	Vec2					mContacts[2];			 // Points of contact during collision
	int						mContactCount;			 // Number of contacts that occured during collision
	float					mMixedRestitution;       // Mixed restitution between the two colliders
	float					mMixedDynamicFriction;   // Mixed dynamic friction between the two colliders
	float					mMixedStaticFriction;	 // Mixed static friction between the two colliders
};

