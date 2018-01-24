#include "GUITextDamageComponent.h"

GUITextDamageComponent::GUITextDamageComponent(DamageableComponent* dmg, int renderLayer) : GUITextComponent(renderLayer)
{
	mDamageableComponent = dmg;
}

GUITextDamageComponent::~GUITextDamageComponent()
{
}

void GUITextDamageComponent::Draw(ICamera * cam)
{
	std::string outputstring = mText;
	std::stringstream stream;
	stream << mText << mDamageableComponent->Health;
	string s = stream.str();

	float rgb[3];
	rgb[0] = mColourR;
	rgb[1] = mColourG;
	rgb[2] = mColourB;
	cam->DrawTextScreenSpace(s, GetTransform()->GetWorldPosition(), GetTransform()->GetWorldRotation(), rgb, GetTransform()->GetWorldScale(), mOffset);
}