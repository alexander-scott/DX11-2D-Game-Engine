#include "SpriteRendererComponent.h"



SpriteRendererComponent::SpriteRendererComponent()
{
	_type = "SpriteRenderer";
}


SpriteRendererComponent::~SpriteRendererComponent()
{
}

void SpriteRendererComponent::Draw(Camera* cam)
{
	cam->DrawSprite(_fileName, GetTransform()->GetPosition(), nullptr, GetTransform()->GetRotation(), GetTransform()->GetScale());
}
