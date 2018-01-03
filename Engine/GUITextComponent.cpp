#include "GUITextComponent.h"


GUITextComponent::GUITextComponent()
{
	mType = "GUITextComponent";
}

GUITextComponent::~GUITextComponent()
{
}

void GUITextComponent::Draw(ICamera* cam)
{
	cam->DrawTextScreenSpace(mText, GetTransform()->GetPosition(), GetTransform()->GetRotation(), GetTransform()->GetScale());
}