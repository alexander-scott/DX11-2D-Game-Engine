#include "TextRendererComponent.h"



TextRendererComponent::TextRendererComponent()
{
}


TextRendererComponent::~TextRendererComponent()
{
}

void TextRendererComponent::Draw(Graphics & gfx)
{
	gfx.DrawTextDX11(_text, GetTransform()->GetPosition());
}
