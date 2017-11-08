#include "TextRendererComponent.h"



TextRendererComponent::TextRendererComponent()
{
	_type = "TextRenderer";
}


TextRendererComponent::~TextRendererComponent()
{
}

void TextRendererComponent::Draw(Graphics & gfx)
{
	gfx.DrawTextDX11(_text, GetTransform()->GetPosition());
}
