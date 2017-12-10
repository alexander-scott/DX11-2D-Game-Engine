#include "GameComponentFactory.h"


PlayerComponent * ComponentFactory::MakePlayerComponent(SpriteAnimatorComponent * anim, RigidBodyComponent * rb)
{
	if (anim == nullptr)
	{
		throw std::exception("This object requires a animator component.");
	}

	if (rb == nullptr)
	{
		throw std::exception("This object requires a rigidbody component.");
	}

	PlayerComponent* playerComponent = new PlayerComponent(anim, rb);

	return playerComponent;
}
