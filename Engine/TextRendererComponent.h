#pragma once

#include "IComponent.h"
#include "IDrawable.h"

class TextRendererComponent : public IComponent, public IDrawable
{
public:
	TextRendererComponent();
	~TextRendererComponent();

	void SetText(std::string text) { _text = text; }

	virtual void Draw(Camera* cam) override;

private:
	std::string _text;
};

