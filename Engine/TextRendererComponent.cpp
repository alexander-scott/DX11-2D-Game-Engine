#include "TextRendererComponent.h"



TextRendererComponent::TextRendererComponent()
{
	_type = "TextRenderer";
}


TextRendererComponent::~TextRendererComponent()
{
}

void TextRendererComponent::Draw(IGraphics & gfx)
{
	gfx.DrawText(_text, GetTransform()->GetPosition());
}
