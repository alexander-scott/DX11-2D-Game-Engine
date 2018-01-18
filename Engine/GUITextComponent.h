#pragma once

#include "IComponent.h"
#include "IDrawable.h"

class GUITextComponent : public IComponent, public IDrawable
{
public:
	GUITextComponent(int renderLayer);
	~GUITextComponent();

	void SetText(std::string text) { mText = text; }
	void SetTextColour(float r, float g, float b) { mColourR = r; mColourG = g; mColourB = b; }
	void SetOffset(Vec2 offset) { mOffset = offset; }

	virtual void Draw(ICamera* cam) override;

protected:
	std::string			mText;
	float				mColourR;
	float				mColourG;
	float				mColourB;
	Vec2				mOffset;
};

