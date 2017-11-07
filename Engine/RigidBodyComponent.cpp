#include "RigidBodyComponent.h"
#include "AddForceMessage.h"


RigidBodyComponent::RigidBodyComponent()
{
	velocity.Set(0, 0);
	angularVelocity = 0;
	torque = 0;
	orient = Random(-PI, PI);
	force.Set(0, 0);
	staticFriction = 0.5f;
	dynamicFriction = 0.3f;
	restitution = 0.2f;
}


RigidBodyComponent::~RigidBodyComponent()
{
}

void RigidBodyComponent::Update(float deltaTime)
{
	if (im == 0.0f)
		return;

	velocity *= 0.98f;
	force *= 0.95f;

	transformComponent->SetPosition(transformComponent->GetPosition() + velocity * dt);

	orient += angularVelocity * dt;
	SetOrient(orient);

	velocity += (force * im + gravity) * (dt / 2.0f);
	angularVelocity += torque * iI * (dt / 2.0f);
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
