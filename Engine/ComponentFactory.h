#pragma once

#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include "SpriteAnimatorComponent.h"
#include "RigidBodyComponent.h"

namespace ComponentFactory
{
	TransformComponent * MakeTransform(Vec2 position);
	SpriteRendererComponent * MakeSpriteRenderer(std::string fileName, TransformComponent* transform);
	SpriteAnimatorComponent * MakeSpriteAnimator(std::string fileName, TransformComponent* transform, std::vector<AnimationDesc> animDescs);
	RigidBodyComponent * MakeRigidbody(TransformComponent* transform);
};