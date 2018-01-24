#include "GUISpriteRendererComponent.h"



GUISpriteRendererComponent::GUISpriteRendererComponent(int renderLayer) : SpriteRendererComponent(renderLayer)
{
	mType = "GUI Sprite Renderer";
}


GUISpriteRendererComponent::~GUISpriteRendererComponent()
{
}

void GUISpriteRendererComponent::Draw(ICamera * cam)
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

	cam->DrawSpriteScreenSpace(mSpriteFileName, Vec2(newPosX, newPosY), nullptr, trans->GetWorldRotation(), trans->GetWorldScale(), mOffset);
}
