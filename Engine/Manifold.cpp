#include "Manifold.h"


Manifold::~Manifold()
{
}

void Manifold::Solve(void)
{
	if (cA->GetType() == ColliderType::eCircle && cB->GetType() == ColliderType::eCircle) // Circle to circle
	{
		CircletoCircle();
	}
	else if (cA->GetType() == ColliderType::eCircle && cB->GetType() == ColliderType::ePolygon) // Circle to polygon
	{
		CircleToPolygon();
	}
	else if (cA->GetType() == ColliderType::ePolygon && cB->GetType() == ColliderType::eCircle) // Polygon to circle
	{
		PolygonToCircle();
	}
	else if (cA->GetType() == ColliderType::ePolygon && cB->GetType() == ColliderType::ePolygon) // Polygon to polygon
	{
		PolygonToPolygon();
	}
}

void Manifold::Initialize(void)
{
	// Calculate average restitution
	e = std::min(cA->GetRigidbodyComponent()->restitution, cB->GetRigidbodyComponent()->restitution);

	// Calculate static and dynamic friction
	sf = std::sqrt(cA->GetRigidbodyComponent()->staticFriction * cB->GetRigidbodyComponent()->staticFriction);
	df = std::sqrt(cA->GetRigidbodyComponent()->dynamicFriction * cB->GetRigidbodyComponent()->dynamicFriction);

	for (uint32 i = 0; i < contact_count; ++i)
	{
		// Calculate radii from COM to contact
		Vec2 ra = contacts[i] - cA->GetTransformComponent()->GetPosition();
		Vec2 rb = contacts[i] - cB->GetTransformComponent()->GetPosition();

		Vec2 rv = cB->GetRigidbodyComponent()->velocity + Cross(cB->GetRigidbodyComponent()->angularVelocity, rb) -
			cA->GetRigidbodyComponent()->velocity - Cross(cA->GetRigidbodyComponent()->angularVelocity, ra);


		// Determine if we should perform a resting collision or not
		// The idea is if the only thing moving this object is gravity,
		// then the collision should be performed without any restitution
		if (rv.LenSqr() < (dt * gravity).LenSqr() + EPSILON)
			e = 0.0f;
	}
}

void Manifold::ApplyImpulse(void)
{
	// Early out and positional correct if both objects have infinite mass
	if (Equal(cA->GetRigidbodyComponent()->im + cB->GetRigidbodyComponent()->im, 0))
	{
		InfiniteMassCorrection();
		return;
	}

	for (uint32 i = 0; i < contact_count; ++i)
	{
		// Calculate radii from COM to contact
		Vec2 ra = contacts[i] - cA->GetTransformComponent()->GetPosition();
		Vec2 rb = contacts[i] - cB->GetTransformComponent()->GetPosition();

		// Relative velocity
		Vec2 rv = cB->GetRigidbodyComponent()->velocity + Cross(cB->GetRigidbodyComponent()->angularVelocity, rb) -
			cA->GetRigidbodyComponent()->velocity - Cross(cA->GetRigidbodyComponent()->angularVelocity, ra);

		// Relative velocity along the normal
		float contactVel = Dot(rv, normal);

		// Do not resolve if velocities are separating
		if (contactVel > 0)
			return;

		float raCrossN = Cross(ra, normal);
		float rbCrossN = Cross(rb, normal);
		float invMassSum = cA->GetRigidbodyComponent()->im + cB->GetRigidbodyComponent()->im + Sqr(raCrossN) * cA->GetRigidbodyComponent()->iI + Sqr(rbCrossN) * cB->GetRigidbodyComponent()->iI;

		// Calculate impulse scalar
		float j = -(1.0f + e) * contactVel;
		j /= invMassSum;
		j /= (float)contact_count;

		// Apply impulse
		Vec2 impulse = normal * j;
		cA->GetRigidbodyComponent()->ApplyImpulse(-impulse, ra);
		cB->GetRigidbodyComponent()->ApplyImpulse(impulse, rb);

		// Friction impulse
		rv = cB->GetRigidbodyComponent()->velocity + Cross(cB->GetRigidbodyComponent()->angularVelocity, rb) -
			cA->GetRigidbodyComponent()->velocity - Cross(cA->GetRigidbodyComponent()->angularVelocity, ra);

		Vec2 t = rv - (normal * Dot(rv, normal));
		t.Normalize();

		// j tangent magnitude
		float jt = -Dot(rv, t);
		jt /= invMassSum;
		jt /= (float)contact_count;

		// Don't apply tiny friction impulses
		if (Equal(jt, 0.0f))
			return;

		// Coulumb's law
		Vec2 tangentImpulse;
		if (std::abs(jt) < j * sf)
			tangentImpulse = t * jt;
		else
			tangentImpulse = t * -j * df;

		// Apply friction impulse
		cA->GetRigidbodyComponent()->ApplyImpulse(-tangentImpulse, ra);
		cB->GetRigidbodyComponent()->ApplyImpulse(tangentImpulse, rb);
	}
}

void Manifold::PositionalCorrection(void)
{
	const float k_slop = 0.05f; // Penetration allowance
	const float percent = 0.4f; // Penetration percentage to correct
	Vec2 correction = (std::max(penetration - k_slop, 0.0f) / (cA->GetRigidbodyComponent()->im + cB->GetRigidbodyComponent()->im)) * normal * percent;
	cA->GetTransformComponent()->SetPosition(cA->GetTransformComponent()->GetPosition() - correction * cA->GetRigidbodyComponent()->im);
	cB->GetTransformComponent()->SetPosition(cB->GetTransformComponent()->GetPosition() + correction * cB->GetRigidbodyComponent()->im);
}

void Manifold::InfiniteMassCorrection(void)
{
	cA->GetRigidbodyComponent()->velocity = Vec2(0, 0);
	cB->GetRigidbodyComponent()->velocity = Vec2(0, 0);
}

void Manifold::CircletoCircle()
{
	CircleColliderComponent *A = reinterpret_cast<CircleColliderComponent *>(cA);
	CircleColliderComponent *B = reinterpret_cast<CircleColliderComponent *>(cB);

	// Calculate translational vector, which is normal
	Vec2 normal = B->GetTransformComponent()->GetPosition() - A->GetTransformComponent()->GetPosition();

	float dist_sqr = normal.LenSqr();
	float radius = A->GetRadius() + B->GetRadius();

	// Not in contact
	if (dist_sqr >= radius * radius)
	{
		contact_count = 0;
		return;
	}

	real distance = std::sqrt(dist_sqr);

	contact_count = 1;

	if (distance == 0.0f)
	{
		penetration = A->GetRadius();
		normal = Vec2(1, 0);
		contacts[0] = A->GetTransformComponent()->GetPosition();
	}
	else
	{
		penetration = radius - distance;
		normal = normal / distance; // Faster than using Normalized since we already performed sqrt
		contacts[0] = normal * A->GetRadius() + A->GetTransformComponent()->GetPosition();
	}
}

void Manifold::CircleToPolygon()
{
	CircleColliderComponent *A = reinterpret_cast<CircleColliderComponent *>(cA);
	PolygonColliderComponent *B = reinterpret_cast<PolygonColliderComponent *>(cB);

	contact_count = 0;

	// Transform circle center to Polygon model space
	Vec2 center = cA->GetTransformComponent()->GetPosition();
	center = cB->u.Transpose() * (center - cB->GetTransformComponent()->GetPosition());

	// Find edge with minimum penetration
	// Exact concept as using support points in Polygon vs Polygon
	real separation = -FLT_MAX;
	uint32 faceNormal = 0;
	for (uint32 i = 0; i < B->m_vertexCount; ++i)
	{
		real s = Dot(B->m_normals[i], center - B->m_vertices[i]);

		if (s > A->radius)
			return;

		if (s > separation)
		{
			separation = s;
			faceNormal = i;
		}
	}

	// Grab face's vertices
	Vec2 v1 = B->m_vertices[faceNormal];
	uint32 i2 = faceNormal + 1 < B->m_vertexCount ? faceNormal + 1 : 0;
	Vec2 v2 = B->m_vertices[i2];

	// Check to see if center is within polygon
	if (separation < EPSILON)
	{
		contact_count = 1;
		normal = -(B->u * B->m_normals[faceNormal]);
		contacts[0] = normal * A->radius + cA->GetTransformComponent()->GetPosition();
		penetration = A->radius;
		return;
	}

	// Determine which voronoi region of the edge center of circle lies within
	real dot1 = Dot(center - v1, v2 - v1);
	real dot2 = Dot(center - v2, v1 - v2);
	penetration = A->radius - separation;

	// Closest to v1
	if (dot1 <= 0.0f)
	{
		if (DistSqr(center, v1) > A->radius * A->radius)
			return;

		contact_count = 1;
		Vec2 n = v1 - center;
		n = B->u * n;
		n.Normalize();
		normal = n;
		v1 = B->u * v1 + cB->GetTransformComponent()->GetPosition();
		contacts[0] = v1;
	}

	// Closest to v2
	else if (dot2 <= 0.0f)
	{
		if (DistSqr(center, v2) > A->radius * A->radius)
			return;

		contact_count = 1;
		Vec2 n = v2 - center;
		v2 = B->u * v2 + cB->GetTransformComponent()->GetPosition();
		contacts[0] = v2;
		n = B->u * n;
		n.Normalize();
		normal = n;
	}

	// Closest to face
	else
	{
		Vec2 n = B->m_normals[faceNormal];
		if (Dot(center - v1, n) > A->radius)
			return;

		n = B->u * n;
		normal = -n;
		contacts[0] = normal * A->radius + cA->GetTransformComponent()->GetPosition();
		contact_count = 1;
	}
}

void Manifold::PolygonToCircle()
{
	ColliderComponent* cC = cA;
	cA = cB;
	cB = cA;
	normal = -normal;

	CircleToPolygon();
}

void Manifold::PolygonToPolygon()
{
	PolygonColliderComponent *A = reinterpret_cast<PolygonColliderComponent *>(cA);
	PolygonColliderComponent *B = reinterpret_cast<PolygonColliderComponent *>(cB);
	contact_count = 0;

	// Check for a separating axis with A's face planes
	uint32 faceA;
	real penetrationA = FindAxisLeastPenetration(&faceA, A, B);
	if (penetrationA >= 0.0f)
		return;

	// Check for a separating axis with B's face planes
	uint32 faceB;
	real penetrationB = FindAxisLeastPenetration(&faceB, B, A);
	if (penetrationB >= 0.0f)
		return;

	uint32 referenceIndex;
	bool flip; // Always point from a to b

	PolygonColliderComponent *RefPoly; // Reference
	PolygonColliderComponent *IncPoly; // Incident

						   // Determine which shape contains reference face
	if (BiasGreaterThan(penetrationA, penetrationB))
	{
		RefPoly = A;
		IncPoly = B;
		referenceIndex = faceA;
		flip = false;
	}

	else
	{
		RefPoly = B;
		IncPoly = A;
		referenceIndex = faceB;
		flip = true;
	}

	// World space incident face
	Vec2 incidentFace[2];
	FindIncidentFace(incidentFace, RefPoly, IncPoly, referenceIndex);

	//        y
	//        ^  ->n       ^
	//      +---c ------posPlane--
	//  x < | i |\
	  //      +---+ c-----negPlane--
//             \       v
//              r
//
//  r : reference face
//  i : incident poly
//  c : clipped point
//  n : incident normal

// Setup reference face vertices
	Vec2 v1 = RefPoly->m_vertices[referenceIndex];
	referenceIndex = referenceIndex + 1 == RefPoly->m_vertexCount ? 0 : referenceIndex + 1;
	Vec2 v2 = RefPoly->m_vertices[referenceIndex];

	// Transform vertices to world space
	v1 = RefPoly->u * v1 + RefPoly->GetTransformComponent()->GetPosition();
	v2 = RefPoly->u * v2 + RefPoly->GetTransformComponent()->GetPosition();

	// Calculate reference face side normal in world space
	Vec2 sidePlaneNormal = (v2 - v1);
	sidePlaneNormal.Normalize();

	// Orthogonalize
	Vec2 refFaceNormal(sidePlaneNormal.y, -sidePlaneNormal.x);

	// ax + by = c
	// c is distance from origin
	real refC = Dot(refFaceNormal, v1);
	real negSide = -Dot(sidePlaneNormal, v1);
	real posSide = Dot(sidePlaneNormal, v2);

	// Clip incident face to reference face side planes
	if (Clip(-sidePlaneNormal, negSide, incidentFace) < 2)
		return; // Due to floating point error, possible to not have required points

	if (Clip(sidePlaneNormal, posSide, incidentFace) < 2)
		return; // Due to floating point error, possible to not have required points

				// Flip
	normal = flip ? -refFaceNormal : refFaceNormal;

	// Keep points behind reference face
	uint32 cp = 0; // clipped points behind reference face
	real separation = Dot(refFaceNormal, incidentFace[0]) - refC;
	if (separation <= 0.0f)
	{
		contacts[cp] = incidentFace[0];
		penetration = -separation;
		++cp;
	}
	else
		penetration = 0;

	separation = Dot(refFaceNormal, incidentFace[1]) - refC;
	if (separation <= 0.0f)
	{
		contacts[cp] = incidentFace[1];

		penetration += -separation;
		++cp;

		// Average penetration
		penetration /= (real)cp;
	}

	contact_count = cp;
}

float Manifold::FindAxisLeastPenetration(uint32 * faceIndex, PolygonColliderComponent * A, PolygonColliderComponent * B)
{
	real bestDistance = -100000;
	uint32 bestIndex;

	for (uint32 i = 0; i < A->m_vertexCount; ++i)
	{
		// Retrieve a face normal from A
		Vec2 n = A->m_normals[i];
		Vec2 nw = A->u * n;

		// Transform face normal into B's model space
		Mat2 buT = B->u.Transpose();
		n = buT * nw;

		// Retrieve support point from B along -n
		Vec2 s = B->GetSupport(-n);

		// Retrieve vertex on face from A, transform into
		// B's model space
		Vec2 v = A->m_vertices[i];
		v = A->u * v + A->GetTransformComponent()->GetPosition();
		v -= B->GetTransformComponent()->GetPosition();
		v = buT * v;

		// Compute penetration distance (in B's model space)
		real d = Dot(n, s - v);

		// Store greatest distance
		if (d > bestDistance)
		{
			bestDistance = d;
			bestIndex = i;
		}
	}

	*faceIndex = bestIndex;
	return bestDistance;
}

void Manifold::FindIncidentFace(Vec2 * v, PolygonColliderComponent * RefPoly, PolygonColliderComponent * IncPoly, uint32 referenceIndex)
{
	Vec2 referenceNormal = RefPoly->m_normals[referenceIndex];

	// Calculate normal in incident's frame of reference
	referenceNormal = RefPoly->u * referenceNormal; // To world space
	referenceNormal = IncPoly->u.Transpose() * referenceNormal; // To incident's model space

																// Find most anti-normal face on incident polygon
	int32 incidentFace = 0;
	real minDot = FLT_MAX;
	for (uint32 i = 0; i < IncPoly->m_vertexCount; ++i)
	{
		real dot = Dot(referenceNormal, IncPoly->m_normals[i]);
		if (dot < minDot)
		{
			minDot = dot;
			incidentFace = i;
		}
	}

	// Assign face vertices for incidentFace
	v[0] = IncPoly->u * IncPoly->m_vertices[incidentFace] + IncPoly->GetTransformComponent()->GetPosition();
	incidentFace = incidentFace + 1 >= (int32)IncPoly->m_vertexCount ? 0 : incidentFace + 1;
	v[1] = IncPoly->u * IncPoly->m_vertices[incidentFace] + IncPoly->GetTransformComponent()->GetPosition();
}

int32 Manifold::Clip(Vec2 n, real c, Vec2 * face)
{
	uint32 sp = 0;
	Vec2 out[2] = {
		face[0],
		face[1]
	};

	// Retrieve distances from each endpoint to the line
	// d = ax + by - c
	real d1 = Dot(n, face[0]) - c;
	real d2 = Dot(n, face[1]) - c;

	// If negative (behind plane) clip
	if (d1 <= 0.0f) out[sp++] = face[0];
	if (d2 <= 0.0f) out[sp++] = face[1];

	// If the points are on different sides of the plane
	if (d1 * d2 < 0.0f) // less than to ignore -0.0f
	{
		// Push interesection point
		real alpha = d1 / (d1 - d2);
		out[sp] = face[0] + alpha * (face[1] - face[0]);
		++sp;
	}

	// Assign our new converted values
	face[0] = out[0];
	face[1] = out[1];

	assert(sp != 3);

	return sp;
}
