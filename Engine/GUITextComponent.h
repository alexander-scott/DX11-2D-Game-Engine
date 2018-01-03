#pragma once

#include "IComponent.h"
#include "IDrawable.h"

class GUITextComponent : public IComponent, public IDrawable
{
public:
	GUITextComponent();
	~GUITextComponent();

	void SetText(std::string text) { mText = text; }
	void SetTextColour(XMVECTORF32 colour) { mTextColour = colour; }

	virtual void Draw(ICamera* cam) override;

protected:
	std::string mText;
	XMVECTORF32 mTextColour;
};

