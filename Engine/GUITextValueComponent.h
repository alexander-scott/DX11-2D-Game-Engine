#pragma once

#include "GUITextComponent.h"

#include <sstream> // stringstream

class GUITextValueComponent : public GUITextComponent
{
public:
	GUITextValueComponent(float& watchValue);
	~GUITextValueComponent();

	virtual void Draw(ICamera* cam) override;

private:
	float&		mWatchedValue;
};