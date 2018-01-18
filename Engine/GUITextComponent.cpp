#include "GUITextComponent.h"


GUITextComponent::GUITextComponent(int renderLayer)
{
	mType = "GUITextComponent";
	RenderLayer = renderLayer;
}

GUITextComponent::~GUITextComponent()
{
}

void GUITextComponent::Draw(ICamera* cam)
{
	float rgb[3];
	rgb[0] = mColourR;
	rgb[1] = mColourG;
	rgb[2] = mColourB;
	cam->DrawTextScreenSpace(mText, GetTransform()->GetPosition(), GetTransform()->GetRotation(), rgb, GetTransform()->GetScale(), mOffset);
}