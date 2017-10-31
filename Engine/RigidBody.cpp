#include "RigidBody.h"


RigidBody::RigidBody(float x, float y)
{
	position.Set(x, y);
	velocity.Set(0, 0);
	angularVelocity = 0;
	torque = 0;
	orient = Random(-PI, PI);
	force.Set(0, 0);
	staticFriction = 0.5f;
	dynamicFriction = 0.3f;
	restitution = 0.2f;
}

RigidBody::~RigidBody()
{
}

void RigidBody::Update(float dt)
{
	if (im == 0.0f)
		return;

	velocity *= 0.98f;
	force *= 0.95f;

	position += velocity * dt;
	orient += angularVelocity * dt;
	SetOrient(orient);

	velocity += (force * im + gravity) * (dt / 2.0f);
	angularVelocity += torque * iI * (dt / 2.0f);
}

void RigidBody::SetOrient(float radians)
{
	orient = radians;
}
