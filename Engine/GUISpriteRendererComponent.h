#pragma once

#include "SpriteRendererComponent.h"

class GUISpriteRendererComponent : public SpriteRendererComponent
{
public:
	GUISpriteRendererComponent(int renderLayer);
	~GUISpriteRendererComponent();

	virtual void Draw(ICamera* cam) override;
};

