#include "RigidBodyComponent.h"
#include "AddForceMessage.h"


RigidBodyComponent::RigidBodyComponent(float staticF, float dynamicF, float rest)
{
	_type = "Rigidbody";

	rigidbodyData = RigidBodyData(Vec2(0,0), 0, 0, Vec2(0,0), 0, 0, 0);
	
	rigidbodyData.velocity.Set(0, 0);
	rigidbodyData.angularVelocity = 0;
	rigidbodyData.torque = 0;
	rigidbodyData.force.Set(0, 0);
	rigidbodyData.orientationMatrix = 0;
	rigidbodyData.staticFriction = staticF;
	rigidbodyData.dynamicFriction = dynamicF;
	rigidbodyData.restitution = rest;

	_rotationLocked = false;
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

void RigidBodyComponent::ApplyForce(const Vec2& f)
{
	rigidbodyData.force += (f * 1000000);
}

void RigidBodyComponent::ApplyImpulse(const Vec2 & impulse, const Vec2 & contactVector)
{
	rigidbodyData.velocity += rigidbodyData.inverseMass * impulse;
	rigidbodyData.angularVelocity += rigidbodyData.inverseInertia * Cross(contactVector, impulse);
}

void RigidBodyComponent::SetStatic()
{
	rigidbodyData.intertia = 0.0f;
	rigidbodyData.inverseInertia = 0.0f;
	rigidbodyData.mass = 0.0f;
	rigidbodyData.inverseMass = 0.0f;
}
