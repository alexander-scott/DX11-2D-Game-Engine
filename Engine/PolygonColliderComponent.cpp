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

void PolygonColliderComponent::SetBox(float hw, float hh)
{
	m_vertexCount = 4;
	m_vertices[0].Set(-hw, -hh);
	m_vertices[1].Set(hw, -hh);
	m_vertices[2].Set(hw, hh);
	m_vertices[3].Set(-hw, hh);
	m_normals[0].Set(0.0f, -1.0f);
	m_normals[1].Set(1.0f, 0.0f);
	m_normals[2].Set(0.0f, 1.0f);
	m_normals[3].Set(-1.0f, 0.0f);
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
