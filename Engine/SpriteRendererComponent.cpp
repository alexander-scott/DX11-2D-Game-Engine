#include "SpriteRendererComponent.h"



SpriteRendererComponent::SpriteRendererComponent()
{
	mType = "SpriteRenderer";
}


SpriteRendererComponent::~SpriteRendererComponent()
{
}

void SpriteRendererComponent::Draw(ICamera* cam)
{
	TransformComponent* trans = GetTransform();

	float halfSpriteWidth = (mSpriteWidth / 2) * trans->GetScale();
	float halfSpriteHeight = (mSpriteHeight / 2) * trans->GetScale();

	Vec2 pos = trans->GetPosition();
	float newPosX = pos.x
		- halfSpriteWidth * cos(trans->GetRotation())
		+ halfSpriteHeight * sin(trans->GetRotation());

	float newPosY = pos.y
		- halfSpriteHeight * cos(trans->GetRotation())
		- halfSpriteWidth * sin(trans->GetRotation());

	cam->DrawSprite(mSpriteFileName, Vec2(newPosX, newPosY), nullptr, trans->GetRotation(), trans->GetScale(), mOffset);
}
