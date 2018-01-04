#pragma once

#include "SpriteRendererComponent.h"

class GUISpriteRendererComponent : public SpriteRendererComponent
{
public:
	GUISpriteRendererComponent();
	~GUISpriteRendererComponent();

	virtual void Draw(ICamera* cam) override;
};

