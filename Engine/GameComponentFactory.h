#pragma once

#include "ComponentFactory.h"

#include "PlayerComponent.h"
#include "DamageableComponent.h"

namespace ComponentFactory
{
	PlayerComponent * MakePlayerComponent(TransformComponent* trans, SpriteAnimatorComponent* anim, RigidBodyComponent* rb, DamageableComponent* dmg);
	DamageableComponent * MakeDamageableComponent(float startHealth);
}

