#include "SpriteRendererComponent.h"

SpriteRendererComponent::SpriteRendererComponent(int renderLayer)
{
	RenderLayer = renderLayer;
	mType = "SpriteRenderer";
}

SpriteRendererComponent::~SpriteRendererComponent()
{
}

void SpriteRendererComponent::Draw(ICamera* cam)
{
	TransformComponent* trans = GetTransform();

	float halfSpriteWidth = (mSpriteWidth / 2) * trans->GetWorldScale();
	float halfSpriteHeight = (mSpriteHeight / 2) * trans->GetWorldScale();

	Vec2 pos = trans->GetWorldPosition();
	float newPosX = pos.x
		- halfSpriteWidth * cos(trans->GetWorldRotation())
		+ halfSpriteHeight * sin(trans->GetWorldRotation());

	float newPosY = pos.y
		- halfSpriteHeight * cos(trans->GetWorldRotation())
		- halfSpriteWidth * sin(trans->GetWorldRotation());

	cam->DrawSpriteWorldSpace(mSpriteFileName, Vec2(newPosX, newPosY), nullptr, trans->GetWorldRotation(), trans->GetWorldScale(), mOffset);
}
