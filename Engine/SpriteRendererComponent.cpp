#include "SpriteRendererComponent.h"



SpriteRendererComponent::SpriteRendererComponent()
{
	_type = "SpriteRenderer";
}


SpriteRendererComponent::~SpriteRendererComponent()
{
}

void SpriteRendererComponent::Draw(ICamera* cam)
{
	float halfSpriteWidth = _spriteWidth / 2;
	float halfSpriteHeight = _spriteHeight / 2;

	TransformComponent* trans = GetTransform();

	Vec2 pos = trans->GetPosition();
	float newPosX = pos.x
		- halfSpriteWidth * cos(trans->GetRotation())
		+ halfSpriteHeight * sin(trans->GetRotation());

	float newPosY = pos.y
		- halfSpriteHeight * cos(trans->GetRotation())
		- halfSpriteWidth * sin(trans->GetRotation());

	cam->DrawSprite(_fileName, Vec2(newPosX, newPosY), nullptr, trans->GetRotation(), trans->GetScale(), _offset);
}
