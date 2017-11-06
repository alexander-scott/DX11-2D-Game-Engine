#include "SpriteRendererComponent.h"



SpriteRendererComponent::SpriteRendererComponent()
{
	_type = "SpriteRenderer";
}


SpriteRendererComponent::~SpriteRendererComponent()
{
}

void SpriteRendererComponent::Draw(Graphics & gfx)
{
	gfx.DrawSpriteDX11(_fileName, _transform->GetPosition(), _transform->GetRotation());
}
