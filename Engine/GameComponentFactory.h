#pragma once

#include "ComponentFactory.h"

#include "PlayerComponent.h"

namespace ComponentFactory
{
	PlayerComponent * MakePlayerComponent(SpriteAnimatorComponent* anim, RigidBodyComponent* rb);
}

