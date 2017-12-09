#include "PolygonColliderComponent.h"



PolygonColliderComponent::PolygonColliderComponent(TransformComponent* trans, RigidBodyComponent* rb)
{
	_type = "Polygon Collider";

	_transformComponent = trans;
	_rigidyBodyComponent = rb;
}


PolygonColliderComponent::~PolygonColliderComponent()
{
}

void PolygonColliderComponent::ComputeMass(float density)
{
	// Calculate centroid and moment of interia
	_centre = Vec2(0.0f, 0.0f); // centroid
	float area = 0.0f;
	float I = 0.0f;
	const float k_inv3 = 1.0f / 3.0f;

	for (int i1 = 0; i1 < m_vertexCount; ++i1)
	{
		// Triangle vertices, third vertex implied as (0, 0)
		Vec2 p1(m_vertices[i1]);
		uint32 i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
		Vec2 p2(m_vertices[i2]);

		float D = Cross(p1, p2);
		float triangleArea = 0.5f * D;

		area += triangleArea;

		// Use area to weight the centroid average, not just vertex position
		_centre += triangleArea * k_inv3 * (p1 + p2);

		float intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
		float inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;
		I += (0.25f * k_inv3 * D) * (intx2 + inty2);
	}

	_centre *= 1.0f / area;

	// Translate vertices to centroid (make the centroid (0, 0)
	// for the polygon in model space)
	// Not really necessary, but I like doing this anyway
	for (uint32 i = 0; i < m_vertexCount; ++i)
		m_vertices[i] -= _centre;

	_rigidyBodyComponent->SetMass(density * area);
	_rigidyBodyComponent->SetInverseMass(_rigidyBodyComponent->GetMass() ? 1.0f / _rigidyBodyComponent->GetMass() : 0.0f);
	_rigidyBodyComponent->SetIntertia(I * density);
	_rigidyBodyComponent->SetInverseIntertia(_rigidyBodyComponent->GetIntertia() ? 1.0 / _rigidyBodyComponent->GetIntertia() : 0.0f);
}

void PolygonColliderComponent::SetVerticies(Vec2 * vertices, int count)
{
	// No hulls with less than 3 vertices (ensure actual polygon)
	assert(count > 2 && count <= MaxPolyVertexCount);
	count = std::min((int32)count, MaxPolyVertexCount);

	// Find the right most point on the hull
	int32 rightMost = 0;
	float highestXCoord = vertices[0].x;
	for (int i = 1; i < count; ++i)
	{
		float x = vertices[i].x;
		if (x > highestXCoord)
		{
			highestXCoord = x;
			rightMost = i;
		}

		// If matching x then take farthest negative y
		else if (x == highestXCoord)
			if (vertices[i].y < vertices[rightMost].y)
				rightMost = i;
	}

	int32 hull[MaxPolyVertexCount];
	int32 outCount = 0;
	int32 indexHull = rightMost;

	for (;;)
	{
		hull[outCount] = indexHull;

		// Search for next index that wraps around the hull
		// by computing cross products to find the most counter-clockwise
		// vertex in the set, given the previos hull index
		int32 nextHullIndex = 0;
		for (int32 i = 1; i < (int32)count; ++i)
		{
			// Skip if same coordinate as we need three unique
			// points in the set to perform a cross product
			if (nextHullIndex == indexHull)
			{
				nextHullIndex = i;
				continue;
			}

			// Cross every set of three unique vertices
			// Record each counter clockwise third vertex and add
			// to the output hull
			// See : http://www.oocities.org/pcgpe/math2d.html
			Vec2 e1 = vertices[nextHullIndex] - vertices[hull[outCount]];
			Vec2 e2 = vertices[i] - vertices[hull[outCount]];
			float c = Cross(e1, e2);
			if (c < 0.0f)
				nextHullIndex = i;

			// Cross product is zero then e vectors are on same line
			// therefor want to record vertex farthest along that line
			if (c == 0.0f && e2.LenSqr() > e1.LenSqr())
				nextHullIndex = i;
		}

		++outCount;
		indexHull = nextHullIndex;

		// Conclude algorithm upon wrap-around
		if (nextHullIndex == rightMost)
		{
			m_vertexCount = outCount;
			break;
		}
	}

	// Copy vertices into shape's vertices
	for (int i = 0; i < m_vertexCount; ++i)
		m_vertices[i] = vertices[hull[i]];

	// Compute face normals
	for (int i1 = 0; i1 < m_vertexCount; ++i1)
	{
		int i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
		Vec2 face = m_vertices[i2] - m_vertices[i1];

		// Ensure no zero-length edges, because that's bad
		assert(face.LenSqr() > EPSILON * EPSILON);

		// Calculate normal with 2D cross product between vector and scalar
		m_normals[i1] = Vec2(face.y, -face.x);
		m_normals[i1].Normalize();
	}
}

// The extreme point along a direction within a polygon
Vec2 PolygonColliderComponent::GetSupport(const Vec2& dir)
{
	float bestProjection = -FLT_MAX;
	Vec2 bestVertex;

	for (int i = 0; i < m_vertexCount; ++i)
	{
		Vec2 v = m_vertices[i];
		float projection = Dot(v, dir);

		if (projection > bestProjection)
		{
			bestVertex = v;
			bestProjection = projection;
		}
	}

	return bestVertex;
}
