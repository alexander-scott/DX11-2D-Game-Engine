#pragma once

#include "IComponent.h"
#include "IDrawable.h"

class SpriteRendererComponent : public IComponent, public IDrawable
{
public:
	SpriteRendererComponent();
	~SpriteRendererComponent();

	void SetFilename(std::string fileName) { _fileName = fileName; }

	virtual void Draw(Camera* cam) override;

private:
	std::string				 _fileName;
};

