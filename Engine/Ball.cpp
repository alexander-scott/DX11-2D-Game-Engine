#include "Ball.h"



Ball::Ball(float xPos, float yPos)
{
	// TRANSFORM COMPONENT
	TransformComponent* trans = ComponentFactory::MakeTransform(Vec2(xPos, yPos), 0, 1);
	AddComponent(trans);

	// RIGIDBODY COMPONENT
	RigidBodyComponent* rigidbody = ComponentFactory::MakeRigidbody(false); // Cache the rigidbody
	AddComponent(rigidbody);

	// CIRCLE COLLIDER COMPONENT
	AddComponent(ComponentFactory::MakeCircleCollider(96, trans, rigidbody));

	// SPRITE RENDERER COMPONENT
	AddComponent(ComponentFactory::MakeSpriteRenderer("Ball", trans));
}


Ball::~Ball()
{
}
