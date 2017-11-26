#include "TextRendererComponent.h"



TextRendererComponent::TextRendererComponent()
{
	_type = "TextRenderer";
}


TextRendererComponent::~TextRendererComponent()
{
}

void TextRendererComponent::Draw(Camera* cam)
{
	cam->GetGraphics()->DrawText(_text, GetTransform()->GetPosition());
}
