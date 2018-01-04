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
	float rgb[3];
	rgb[0] = mTextColour.f[0];
	rgb[1] = mTextColour.f[1];
	rgb[2] = mTextColour.f[2];
	cam->DrawTextScreenSpace(mText, GetTransform()->GetPosition(), GetTransform()->GetRotation(), rgb, GetTransform()->GetScale(), mOffset);
}