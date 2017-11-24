#pragma once

#include "IComponent.h"
#include "IDrawable.h"
#include "Graphics.h"

class SpriteRendererComponent : public IComponent, public IDrawable
{
public:
	SpriteRendererComponent();
	~SpriteRendererComponent();

	void SetFilename(SpriteName fileName) { _fileName = fileName; }

	virtual void Draw(Graphics& gfx) override;

private:
	SpriteName				 _fileName;
};

