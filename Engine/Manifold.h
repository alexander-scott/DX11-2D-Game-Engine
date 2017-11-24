#pragma once

#include "ColliderComponent.h"
#include "CircleColliderComponent.h"
#include "PolygonColliderComponent.h"

class Manifold
{
public:
	Manifold(ColliderComponent* a, ColliderComponent* b) : cA(a), cB(b) { }
	~Manifold();

	void CircletoCircle();
	void CircleToPolygon();
	void PolygonToCircle();
	void PolygonToPolygon();

	float FindAxisLeastPenetration(int *faceIndex, PolygonColliderComponent *A, PolygonColliderComponent *B);
	void FindIncidentFace(Vec2 *v, PolygonColliderComponent *RefPoly, PolygonColliderComponent *IncPoly, int referenceIndex);
	int Clip(Vec2 n, float c, Vec2 *face);

	void Solve();						// Generate contact information
	void Initialize(float deltaTime);   // Precalculations for impulse solving
	void ApplyImpulse();				// Solve impulse and apply
	void PositionalCorrection();		// Naive correction of positional penetration
	void InfiniteMassCorrection();

	int GetContactCount() { return _contactCount; }

private:
	ColliderComponent* cA;
	ColliderComponent* cB;

	float					_penetration;			 // Depth of penetration from collision
	Vec2					_normal;				 // From A to B
	Vec2					_contacts[2];			 // Points of contact during collision
	int					_contactCount;			 // Number of contacts that occured during collision
	float					_mixedRestitution;       // Mixed restitution
	float					_mixedDynamicFriction;   // Mixed dynamic friction
	float					_mixedStaticFriction;	 // Mixed static friction
};

