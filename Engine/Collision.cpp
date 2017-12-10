#include "Collision.h"


Collision::~Collision()
{
}

void Collision::Solve()
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

void Collision::Initialize(float deltaTime)
{
	// Calculate average restitution
	_mixedRestitution = std::min(cA->GetRigidbodyComponent()->GetRestitution(), cB->GetRigidbodyComponent()->GetRestitution());

	// Calculate static and dynamic friction
	_mixedStaticFriction = std::sqrt(cA->GetRigidbodyComponent()->GetStaticFriction() * cB->GetRigidbodyComponent()->GetStaticFriction());
	_mixedDynamicFriction = std::sqrt(cA->GetRigidbodyComponent()->GetDynamicFriction() * cB->GetRigidbodyComponent()->GetDynamicFriction());

	for (int i = 0; i < _contactCount; ++i)
	{
		// Calculate radii from COM to contact
		Vec2 ra = _contacts[i] - cA->GetTransformComponent()->GetPosition();
		Vec2 rb = _contacts[i] - cB->GetTransformComponent()->GetPosition();

		Vec2 rv = cB->GetRigidbodyComponent()->GetVelocity() + Cross(cB->GetRigidbodyComponent()->GetAngularVelocity(), rb) -
			cA->GetRigidbodyComponent()->GetVelocity() - Cross(cA->GetRigidbodyComponent()->GetAngularVelocity(), ra);


		// Determine if we should perform a resting collision or not
		// The idea is if the only thing moving this object is gravity,
		// then the collision should be performed without any restitution
		if (rv.LenSqr() < (deltaTime * gravity).LenSqr() + EPSILON)
			_mixedRestitution = 0.0f;
	}
}

void Collision::ApplyImpulse()
{
	// Early out and positional correct if both objects have infinite mass
	if (Equal(cA->GetRigidbodyComponent()->GetInverseMass() + cB->GetRigidbodyComponent()->GetInverseMass(), 0))
	{
		InfiniteMassCorrection();
		return;
	}

	for (int i = 0; i < _contactCount; ++i)
	{
		// Calculate radii from COM to contact
		Vec2 ra = _contacts[i] - cA->GetTransformComponent()->GetPosition();
		Vec2 rb = _contacts[i] - cB->GetTransformComponent()->GetPosition();

		// Relative velocity
		Vec2 rv = cB->GetRigidbodyComponent()->GetVelocity() + Cross(cB->GetRigidbodyComponent()->GetAngularVelocity(), rb) -
			cA->GetRigidbodyComponent()->GetVelocity() - Cross(cA->GetRigidbodyComponent()->GetAngularVelocity(), ra);

		// Relative velocity along the normal
		float contactVel = Dot(rv, _normal);

		// Do not resolve if velocities are separating
		if (contactVel > 0)
			return;

		float raCrossN = Cross(ra, _normal);
		float rbCrossN = Cross(rb, _normal);
		float invMassSum = cA->GetRigidbodyComponent()->GetInverseMass() + cB->GetRigidbodyComponent()->GetInverseMass() + 
			Sqr(raCrossN) * cA->GetRigidbodyComponent()->GetInverseIntertia() + Sqr(rbCrossN) * cB->GetRigidbodyComponent()->GetInverseIntertia();

		// Calculate impulse scalar
		float j = -(1.0f + _mixedRestitution) * contactVel;
		j /= invMassSum;
		j /= (float)_contactCount;

		// Apply impulse
		Vec2 impulse = _normal * j;
		cA->GetRigidbodyComponent()->ApplyImpulse(-impulse, ra);
		cB->GetRigidbodyComponent()->ApplyImpulse(impulse, rb);

		// Friction impulse
		rv = cB->GetRigidbodyComponent()->GetVelocity() + Cross(cB->GetRigidbodyComponent()->GetAngularVelocity(), rb) -
			cA->GetRigidbodyComponent()->GetVelocity() - Cross(cA->GetRigidbodyComponent()->GetAngularVelocity(), ra);

		Vec2 t = rv - (_normal * Dot(rv, _normal));
		t.Normalize();

		// j tangent magnitude
		float jt = -Dot(rv, t);
		jt /= invMassSum;
		jt /= (float)_contactCount;

		// Don't apply tiny friction impulses
		if (Equal(jt, 0.0f))
			return;

		// Coulumb's law
		Vec2 tangentImpulse;
		if (std::abs(jt) < j * _mixedStaticFriction)
			tangentImpulse = t * jt;
		else
			tangentImpulse = t * -j * _mixedDynamicFriction;

		// Apply friction impulse
		cA->GetRigidbodyComponent()->ApplyImpulse(-tangentImpulse, ra);
		cB->GetRigidbodyComponent()->ApplyImpulse(tangentImpulse, rb);
	}
}

void Collision::PositionalCorrection()
{
	const float k_slop = 0.05f; // Penetration allowance
	const float percent = 0.4f; // Penetration percentage to correct
	Vec2 correction = (std::max(_penetration - k_slop, 0.0f) / (cA->GetRigidbodyComponent()->GetInverseMass() + cB->GetRigidbodyComponent()->GetInverseMass())) * _normal * percent;
	cA->GetTransformComponent()->SetPosition(cA->GetTransformComponent()->GetPosition() - correction * cA->GetRigidbodyComponent()->GetInverseMass());
	cB->GetTransformComponent()->SetPosition(cB->GetTransformComponent()->GetPosition() + correction * cB->GetRigidbodyComponent()->GetInverseMass());
}

void Collision::InfiniteMassCorrection()
{
	cA->GetRigidbodyComponent()->SetVelocity(Vec2(0, 0));
	cB->GetRigidbodyComponent()->SetVelocity(Vec2(0, 0));
}

void Collision::CircletoCircle()
{
	CircleColliderComponent *A = reinterpret_cast<CircleColliderComponent *>(cA);
	CircleColliderComponent *B = reinterpret_cast<CircleColliderComponent *>(cB);

	// Calculate translational vector, which is normal
	_normal = B->GetTransformComponent()->GetPosition() - A->GetTransformComponent()->GetPosition();

	float dist_sqr = _normal.LenSqr();
	float radius = A->GetRadius() + B->GetRadius();

	// Not in contact
	if (dist_sqr >= radius * radius)
	{
		_contactCount = 0;
		return;
	}

	float distance = std::sqrt(dist_sqr);

	_contactCount = 1;

	if (distance == 0.0f)
	{
		_penetration = A->GetRadius();
		_normal = Vec2(1, 0);
		_contacts[0] = A->GetTransformComponent()->GetPosition();
	}
	else
	{
		_penetration = radius - distance;
		_normal = _normal / distance; // Faster than using Normalized since we already performed sqrt
		_contacts[0] = _normal * A->GetRadius() + A->GetTransformComponent()->GetPosition();
	}
}

void Collision::CircleToPolygon()
{
	CircleColliderComponent *A = reinterpret_cast<CircleColliderComponent *>(cA);
	PolygonColliderComponent *B = reinterpret_cast<PolygonColliderComponent *>(cB);

	_contactCount = 0;

	// Transform circle center to Polygon model space
	Vec2 center = cA->GetTransformComponent()->GetPosition();
	center = cB->GetRigidbodyComponent()->GetOrientationMatrix().Transpose() * (center - cB->GetTransformComponent()->GetPosition());

	// Find edge with minimum penetration
	// Exact concept as using support points in Polygon vs Polygon
	float separation = -FLT_MAX;
	int faceNormal = 0;
	for (int i = 0; i < B->m_vertexCount; ++i)
	{
		float s = Dot(B->m_normals[i], center - B->m_vertices[i]);

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
	int i2 = faceNormal + 1 < B->m_vertexCount ? faceNormal + 1 : 0;
	Vec2 v2 = B->m_vertices[i2];

	// Check to see if center is within polygon
	if (separation < EPSILON)
	{
		_contactCount = 1;
		_normal = -(B->GetRigidbodyComponent()->GetOrientationMatrix() * B->m_normals[faceNormal]);
		_contacts[0] = _normal * A->radius + cA->GetTransformComponent()->GetPosition();
		_penetration = A->radius;
		return;
	}

	// Determine which voronoi region of the edge center of circle lies within
	float dot1 = Dot(center - v1, v2 - v1);
	float dot2 = Dot(center - v2, v1 - v2);
	_penetration = A->radius - separation;

	// Closest to v1
	if (dot1 <= 0.0f)
	{
		if (DistSqr(center, v1) > A->radius * A->radius)
			return;

		_contactCount = 1;
		Vec2 n = v1 - center;
		n = B->GetRigidbodyComponent()->GetOrientationMatrix() * n;
		n.Normalize();
		_normal = n;
		v1 = B->GetRigidbodyComponent()->GetOrientationMatrix() * v1 + cB->GetTransformComponent()->GetPosition();
		_contacts[0] = v1;
	}

	// Closest to v2
	else if (dot2 <= 0.0f)
	{
		if (DistSqr(center, v2) > A->radius * A->radius)
			return;

		_contactCount = 1;
		Vec2 n = v2 - center;
		v2 = B->GetRigidbodyComponent()->GetOrientationMatrix() * v2 + cB->GetTransformComponent()->GetPosition();
		_contacts[0] = v2;
		n = B->GetRigidbodyComponent()->GetOrientationMatrix() * n;
		n.Normalize();
		_normal = n;
	}

	// Closest to face
	else
	{
		Vec2 n = B->m_normals[faceNormal];
		if (Dot(center - v1, n) > A->radius)
			return;

		n = B->GetRigidbodyComponent()->GetOrientationMatrix() * n;
		_normal = -n;
		_contacts[0] = _normal * A->radius + cA->GetTransformComponent()->GetPosition();
		_contactCount = 1;
	}
}

void Collision::PolygonToCircle()
{
	ColliderComponent* cC = cA;
	cA = cB;
	cB = cC;
	_normal = -_normal;

	CircleToPolygon();
}

void Collision::PolygonToPolygon()
{
	PolygonColliderComponent *A = reinterpret_cast<PolygonColliderComponent *>(cA);
	PolygonColliderComponent *B = reinterpret_cast<PolygonColliderComponent *>(cB);
	_contactCount = 0;

	// Check for a separating axis with A's face planes
	int faceA;
	float penetrationA = FindAxisLeastPenetration(&faceA, A, B);
	if (penetrationA >= 0.0f)
		return;

	// Check for a separating axis with B's face planes
	int faceB;
	float penetrationB = FindAxisLeastPenetration(&faceB, B, A);
	if (penetrationB >= 0.0f)
		return;

	int referenceIndex;
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
	v1 = RefPoly->GetRigidbodyComponent()->GetOrientationMatrix() * v1 + RefPoly->GetTransformComponent()->GetPosition();
	v2 = RefPoly->GetRigidbodyComponent()->GetOrientationMatrix() * v2 + RefPoly->GetTransformComponent()->GetPosition();

	// Calculate reference face side normal in world space
	Vec2 sidePlaneNormal = (v2 - v1);
	sidePlaneNormal.Normalize();

	// Orthogonalize
	Vec2 refFaceNormal(sidePlaneNormal.y, -sidePlaneNormal.x);

	// ax + by = c
	// c is distance from origin
	float refC = Dot(refFaceNormal, v1);
	float negSide = -Dot(sidePlaneNormal, v1);
	float posSide = Dot(sidePlaneNormal, v2);

	// Clip incident face to reference face side planes
	if (Clip(-sidePlaneNormal, negSide, incidentFace) < 2)
		return; // Due to floating point error, possible to not have required points

	if (Clip(sidePlaneNormal, posSide, incidentFace) < 2)
		return; // Due to floating point error, possible to not have required points

	// Flip
	_normal = flip ? -refFaceNormal : refFaceNormal;

	// Keep points behind reference face
	int cp = 0; // clipped points behind reference face
	float separation = Dot(refFaceNormal, incidentFace[0]) - refC;
	if (separation <= 0.0f)
	{
		_contacts[cp] = incidentFace[0];
		_penetration = -separation;
		++cp;
	}
	else
		_penetration = 0;

	separation = Dot(refFaceNormal, incidentFace[1]) - refC;
	if (separation <= 0.0f)
	{
		_contacts[cp] = incidentFace[1];

		_penetration += -separation;
		++cp;

		// Average penetration
		_penetration /= (float)cp;
	}

	_contactCount = cp;
}

float Collision::FindAxisLeastPenetration(int * faceIndex, PolygonColliderComponent * A, PolygonColliderComponent * B)
{
	float bestDistance = -100000;
	int bestIndex;

	for (int i = 0; i < A->m_vertexCount; ++i)
	{
		// Retrieve a face normal from A
		Vec2 n = A->m_normals[i];
		Vec2 nw = A->GetRigidbodyComponent()->GetOrientationMatrix() * n;

		// Transform face normal into B's model space
		Mat2 buT = B->GetRigidbodyComponent()->GetOrientationMatrix().Transpose();
		n = buT * nw;

		// Retrieve support point from B along -n
		Vec2 s = B->GetSupport(-n);

		// Retrieve vertex on face from A, transform into
		// B's model space
		Vec2 v = A->m_vertices[i];
		v = A->GetRigidbodyComponent()->GetOrientationMatrix() * v + A->GetTransformComponent()->GetPosition();
		v -= B->GetTransformComponent()->GetPosition();
		v = buT * v;

		// Compute penetration distance (in B's model space)
		float d = Dot(n, s - v);

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

void Collision::FindIncidentFace(Vec2 * v, PolygonColliderComponent * RefPoly, PolygonColliderComponent * IncPoly, int referenceIndex)
{
	Vec2 referenceNormal = RefPoly->m_normals[referenceIndex];

	// Calculate normal in incident's frame of reference
	referenceNormal = RefPoly->GetRigidbodyComponent()->GetOrientationMatrix() * referenceNormal; // To world space
	referenceNormal = IncPoly->GetRigidbodyComponent()->GetOrientationMatrix().Transpose() * referenceNormal; // To incident's model space

	// Find most anti-normal face on incident polygon
	int incidentFace = 0;
	float minDot = FLT_MAX;
	for (int i = 0; i < IncPoly->m_vertexCount; ++i)
	{
		float dot = Dot(referenceNormal, IncPoly->m_normals[i]);
		if (dot < minDot)
		{
			minDot = dot;
			incidentFace = i;
		}
	}

	// Assign face vertices for incidentFace
	v[0] = IncPoly->GetRigidbodyComponent()->GetOrientationMatrix() * IncPoly->m_vertices[incidentFace] + IncPoly->GetTransformComponent()->GetPosition();
	incidentFace = incidentFace + 1 >= (int)IncPoly->m_vertexCount ? 0 : incidentFace + 1;
	v[1] = IncPoly->GetRigidbodyComponent()->GetOrientationMatrix() * IncPoly->m_vertices[incidentFace] + IncPoly->GetTransformComponent()->GetPosition();
}

int Collision::Clip(Vec2 n, float c, Vec2 * face)
{
	int sp = 0;
	Vec2 out[2] = {
		face[0],
		face[1]
	};

	// Retrieve distances from each endpoint to the line
	// d = ax + by - c
	float d1 = Dot(n, face[0]) - c;
	float d2 = Dot(n, face[1]) - c;

	// If negative (behind plane) clip
	if (d1 <= 0.0f) out[sp++] = face[0];
	if (d2 <= 0.0f) out[sp++] = face[1];

	// If the points are on different sides of the plane
	if (d1 * d2 < 0.0f) // less than to ignore -0.0f
	{
		// Push interesection point
		float alpha = d1 / (d1 - d2);
		out[sp] = face[0] + alpha * (face[1] - face[0]);
		++sp;
	}

	// Assign our new converted values
	face[0] = out[0];
	face[1] = out[1];

	assert(sp != 3);

	return sp;
}
