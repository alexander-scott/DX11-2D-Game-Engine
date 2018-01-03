#include "GUITextValueComponent.h"



GUITextValueComponent::GUITextValueComponent(float& watchValue) : mWatchedValue(watchValue)
{

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
	rgb[0] = mTextColour.f[0];
	rgb[1] = mTextColour.f[1];
	rgb[2] = mTextColour.f[2];
	cam->DrawTextScreenSpace(s, GetTransform()->GetPosition(), GetTransform()->GetRotation(), rgb, GetTransform()->GetScale());
}
