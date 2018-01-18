#include "GUITextValueComponent.h"



GUITextValueComponent::GUITextValueComponent(std::string mValueName)
{
	mOffset = Vec2(0, 0);

	mWatchedValue = ScenePersistentValues::Instance().GetPointer<float>(mValueName);
}


GUITextValueComponent::~GUITextValueComponent()
{
}

void GUITextValueComponent::Draw(ICamera * cam)
{
	std::string outputstring = mText;
	std::stringstream stream;
	stream << mText << &mWatchedValue;
	string s = stream.str();

	float rgb[3];
	rgb[0] = mColourR;
	rgb[1] = mColourG;
	rgb[2] = mColourB;
	cam->DrawTextScreenSpace(s, GetTransform()->GetPosition(), GetTransform()->GetRotation(), rgb, GetTransform()->GetScale(), mOffset);
}
