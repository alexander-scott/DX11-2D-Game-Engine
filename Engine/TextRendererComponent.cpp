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
	gfx.DrawText(_text, GetTransform()->GetPosition());
}
