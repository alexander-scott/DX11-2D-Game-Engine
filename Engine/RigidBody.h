#pragma once

#include "IEMath.h"

class RigidBody
{
public:
	RigidBody(float x, float y);
	~RigidBody();

	void Update(float dt);

	void SetOrient(float radians);

	void ApplyForce(const Vec2& f)
	{
		force += f;
	}

	void ApplyImpulse(const Vec2& impulse, const Vec2& contactVector)
	{
		velocity += im * impulse;
		angularVelocity += iI * Cross(contactVector, impulse);
	}

	void SetStatic(void)
	{
		I = 0.0f;
		iI = 0.0f;
		m = 0.0f;
		im = 0.0f;
	}

	Vec2 position;
	Vec2 velocity;

	float angularVelocity;
	float torque;
	float orient; // radians

	Vec2 force;

	// Set by shape
	float I;  // moment of inertia
	float iI; // inverse inertia
	float m;  // mass
	float im; // inverse masee

	float staticFriction;
	float dynamicFriction;
	float restitution;
};

