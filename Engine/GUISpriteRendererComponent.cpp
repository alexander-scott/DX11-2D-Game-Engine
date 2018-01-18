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

	float halfSpriteWidth = (mSpriteWidth / 2) * trans->GetScale();
	float halfSpriteHeight = (mSpriteHeight / 2) * trans->GetScale();

	Vec2 pos = trans->GetPosition();
	float newPosX = pos.x
		- halfSpriteWidth * cos(trans->GetRotation())
		+ halfSpriteHeight * sin(trans->GetRotation());

	float newPosY = pos.y
		- halfSpriteHeight * cos(trans->GetRotation())
		- halfSpriteWidth * sin(trans->GetRotation());

	cam->DrawSpriteScreenSpace(mSpriteFileName, Vec2(newPosX, newPosY), nullptr, trans->GetRotation(), trans->GetScale(), mOffset);
}
