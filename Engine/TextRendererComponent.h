#pragma once

#include "IComponent.h"
#include "IDrawable.h"

class TextRendererComponent : public IComponent, public IDrawable
{
public:
	TextRendererComponent();
	~TextRendererComponent();

	void SetText(std::string text) { mText = text; }
	void SetTextColour(XMVECTORF32 colour) { mTextColour = colour; }

	virtual void Draw(ICamera* cam) override;

private:
	std::string mText;
	XMVECTORF32 mTextColour;
};

