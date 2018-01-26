#include "GUITextValueComponent.h"



GUITextValueComponent::GUITextValueComponent(std::string mValueName, int renderLayer) 
	: mWatchedValue(ScenePersistentValues::Instance().GetRef<float>(mValueName)), GUITextComponent(renderLayer)
{
	mOffset = Vec2(0, 0);
}


GUITextValueComponent::~GUITextValueComponent()
{
}

void GUITextValueComponent::Draw(ICamera * cam)
{
	std::string outputstring = mText;
	std::stringstream stream;
	stream << mText << mWatchedValue;
	string s = stream.str();

	float rgb[3];
	rgb[0] = mColourR;
	rgb[1] = mColourG;
	rgb[2] = mColourB;
	cam->DrawTextScreenSpace(s, GetTransform()->GetWorldPosition(), GetTransform()->GetWorldRotation(), rgb, GetTransform()->GetWorldScale(), mOffset);
}
