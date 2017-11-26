#include "TextRendererComponent.h"



TextRendererComponent::TextRendererComponent()
{
	_type = "TextRenderer";
}


TextRendererComponent::~TextRendererComponent()
{
}

void TextRendererComponent::Draw(ICamera* cam)
{
	cam->DrawText(_text, GetTransform()->GetPosition());
}
