#include "TextRendererComponent.h"



TextRendererComponent::TextRendererComponent()
{
	mType = "TextRenderer";
	mOffset = Vec2(0, 0);
}

TextRendererComponent::~TextRendererComponent()
{
}

void TextRendererComponent::Draw(ICamera* cam)
{
	auto colour = DirectX::Colors::Yellow;
	float rgb[3];
	rgb[0] = colour.f[0];
	rgb[1] = colour.f[1];
	rgb[2] = colour.f[2];
	cam->DrawTextWorldSpace(mText, GetTransform()->GetWorldPosition(), GetTransform()->GetWorldRotation(), rgb, GetTransform()->GetWorldScale(), mOffset);
}
