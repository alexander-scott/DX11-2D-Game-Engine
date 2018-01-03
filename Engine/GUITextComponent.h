#pragma once

#include "IComponent.h"
#include "IDrawable.h"

class GUITextComponent : public IComponent, public IDrawable
{
public:
	GUITextComponent();
	~GUITextComponent();

	void SetText(std::string text) { mText = text; }

	virtual void Draw(ICamera* cam) override;

private:
	std::string mText;
};

