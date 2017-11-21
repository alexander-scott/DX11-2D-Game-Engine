#include "RigidBodyComponent.h"
#include "AddForceMessage.h"


RigidBodyComponent::RigidBodyComponent()
{
	_type = "Rigidbody";

	velocity.Set(0, 0);
	angularVelocity = 0;
	torque = 0;
	orient = Random(-PI, PI);
	force.Set(0, 0);
	staticFriction = 1;
	dynamicFriction = 0.3f;
	restitution = 0.5f;
}


RigidBodyComponent::~RigidBodyComponent()
{
}

void RigidBodyComponent::RecieveMessage(IMessage & message)
{
	switch (message.GetType())
	{
	case MessageType::AddForce:
		AddForceMessage& addForceMsg = static_cast<AddForceMessage &> (message);
		ApplyForce(addForceMsg.GetForce());
		break;
	}
}

void RigidBodyComponent::SetOrient(float radians)
{
	orient = radians;
}

void RigidBodyComponent::ApplyForce(const Vec2& f)
{
	force += f;
}

void RigidBodyComponent::ApplyImpulse(const Vec2 & impulse, const Vec2 & contactVector)
{
	velocity += im * impulse;
	angularVelocity += iI * Cross(contactVector, impulse);
}

void RigidBodyComponent::SetStatic()
{
	I = 0.0f;
	iI = 0.0f;
	m = 0.0f;
	im = 0.0f;
}
