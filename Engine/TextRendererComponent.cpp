#include "TextRendererComponent.h"



TextRendererComponent::TextRendererComponent()
{
	mType = "TextRenderer";
}

TextRendererComponent::~TextRendererComponent()
{
}

void TextRendererComponent::Draw(ICamera* cam)
{
	cam->DrawTextWorldSpace(mText, GetTransform()->GetPosition(), GetTransform()->GetRotation(), GetTransform()->GetScale());
}
