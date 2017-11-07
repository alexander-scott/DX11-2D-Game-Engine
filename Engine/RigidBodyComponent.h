#pragma once

#include "IComponent.h"
#include "IUpdateable.h"
#include "IMessageable.h"

#include "TransformComponent.h"

class RigidBodyComponent : public IComponent, public IUpdateable, public IMessageable
{
public:
	RigidBodyComponent();
	~RigidBodyComponent();

	virtual void Update(float deltaTime) override;
	virtual void RecieveMessage(IMessage& message) override;

	void SetTransform(TransformComponent* transform) { transformComponent = transform; }
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

private:
	TransformComponent* transformComponent;

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

