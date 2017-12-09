#pragma once

#include "IComponent.h"
#include "IDrawable.h"

class SpriteRendererComponent : public IComponent, public IDrawable
{
public:
	SpriteRendererComponent();
	~SpriteRendererComponent();

	void SetFilename(std::string fileName) { _fileName = fileName; }
	void SetOffset(Vec2 offset) { _offset = offset; }
	void SetWidthHeight(float wid, float hei) { _spriteWidth = wid; _spriteHeight = hei; }

	virtual void Draw(ICamera* cam) override;

private:
	std::string				 _fileName;
	Vec2					 _offset;

	float					_spriteWidth;
	float					_spriteHeight;
};

