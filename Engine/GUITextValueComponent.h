#pragma once

#include "GUITextComponent.h"
#include "ScenePersistentValues.h"

#include <sstream> // stringstream

class GUITextValueComponent : public GUITextComponent
{
public:
	GUITextValueComponent(std::string mValueName);
	~GUITextValueComponent();

	virtual void Draw(ICamera* cam) override;

private:
	float*			mWatchedValue;
	std::string		mValueName;
};