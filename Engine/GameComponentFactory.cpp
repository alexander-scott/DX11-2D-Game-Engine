#include "GameComponentFactory.h"


PlayerComponent * ComponentFactory::MakePlayerComponent(TransformComponent* trans, SpriteAnimatorComponent * anim, RigidBodyComponent * rb)
{
	if (anim == nullptr)
	{
		throw std::exception("This object requires a animator component.");
	}

	if (rb == nullptr)
	{
		throw std::exception("This object requires a rigidbody component.");
	}

	PlayerComponent* playerComponent = new PlayerComponent(trans, anim, rb);

	return playerComponent;
}
