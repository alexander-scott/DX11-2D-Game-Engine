#pragma once

#include "TransformComponent.h"
#include "SpriteRendererComponent.h"

namespace ComponentFactory
{
	TransformComponent * MakeTransform(Vec2 position);
	SpriteRendererComponent * MakeSpriteRenderer(std::string fileName, TransformComponent* transform);
};