#pragma once

#include "IComponent.h"
#include "IDrawable.h"

class SpriteRendererComponent : public IComponent, public IDrawable
{
public:
	SpriteRendererComponent();
	~SpriteRendererComponent();

	void SetFilename(std::string fileName) { mSpriteFileName = fileName; }
	void SetOffset(Vec2 offset) { mOffset = offset; }
	void SetWidthHeight(float wid, float hei) { mSpriteWidth = wid; mSpriteHeight = hei; }

	virtual void Draw(ICamera* cam) override;

private:
	std::string				 mSpriteFileName;
	Vec2					 mOffset;

	float					mSpriteWidth;
	float					mSpriteHeight;
};

