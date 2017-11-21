#pragma once

#include "IComponent.h"
#include "IUpdateable.h"
#include "IMessageable.h"

#include "TransformComponent.h"

class RigidBodyComponent : public IComponent, public IMessageable
{
public:
	RigidBodyComponent();
	~RigidBodyComponent();

	virtual void RecieveMessage(IMessage& message) override;

	void SetTransform(TransformComponent* transform) { transformComponent = transform; }
	void SetOrient(float radians);

	void ApplyForce(const Vec2& f);
	void ApplyImpulse(const Vec2& impulse, const Vec2& contactVector);

	void SetStatic();

	Vec2 GetVelocity() { return velocity; }
	Vec2 GetPosition() { return transformComponent->GetPosition(); }

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

