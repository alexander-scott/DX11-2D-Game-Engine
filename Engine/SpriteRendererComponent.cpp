#include "SpriteRendererComponent.h"



SpriteRendererComponent::SpriteRendererComponent()
{
	_type = "SpriteRenderer";
}


SpriteRendererComponent::~SpriteRendererComponent()
{
}

void SpriteRendererComponent::Draw(IGraphics & gfx)
{
	gfx.DrawSprite(_fileName, GetTransform()->GetPosition(), nullptr, GetTransform()->GetRotation(), GetTransform()->GetScale());
}
