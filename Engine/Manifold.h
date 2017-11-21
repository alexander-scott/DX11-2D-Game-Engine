#pragma once

#include "ColliderComponent.h"
#include "CircleColliderComponent.h"
#include "PolygonColliderComponent.h"

class Manifold
{
public:
	Manifold(ColliderComponent* a, ColliderComponent* b) : cA(a), cB(b)
	{

	}
	~Manifold();

	void CircletoCircle();
	void CircleToPolygon();
	void PolygonToCircle();
	void PolygonToPolygon();

	float FindAxisLeastPenetration(uint32 *faceIndex, PolygonColliderComponent *A, PolygonColliderComponent *B);
	void FindIncidentFace(Vec2 *v, PolygonColliderComponent *RefPoly, PolygonColliderComponent *IncPoly, uint32 referenceIndex);
	int32 Clip(Vec2 n, real c, Vec2 *face);

	void Solve(void);                 // Generate contact information
	void Initialize(float deltaTime);            // Precalculations for impulse solving
	void ApplyImpulse(void);          // Solve impulse and apply
	void PositionalCorrection(void);  // Naive correction of positional penetration
	void InfiniteMassCorrection(void);

	ColliderComponent* cA;
	ColliderComponent* cB;

	float penetration;     // Depth of penetration from collision
	Vec2 normal;          // From A to B
	Vec2 contacts[2];     // Points of contact during collision
	uint32 contact_count; // Number of contacts that occured during collision
	float e;               // Mixed restitution
	float df;              // Mixed dynamic friction
	float sf;              // Mixed static friction
};

