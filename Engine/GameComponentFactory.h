#pragma once

#include "ComponentFactory.h"

#include "PlayerComponent.h"

namespace ComponentFactory
{
	PlayerComponent * MakePlayerComponent(TransformComponent* trans, SpriteAnimatorComponent* anim, RigidBodyComponent* rb);
}

