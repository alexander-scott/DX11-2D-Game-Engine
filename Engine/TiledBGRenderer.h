#pragma once

#include "IComponent.h"
#include "IDrawable.h"
#include "IUpdateable.h"
#include "TransformComponent.h"

#include <vector>

/*
Move transform by MOVERATE * FocusTransform movement.
Multiply transform by tile width + height to find the 9 closest tile centres to FocusTransform.
Draw the sprite on these 9 tiles.
*/

class TiledBGRenderer : public IComponent, public IDrawable, public IUpdateable
{
public:
	TiledBGRenderer();
	~TiledBGRenderer();

	virtual void Draw(ICamera* cam) override;
	virtual void Update(float deltaTime) override;

	void SetFocusTrans(TransformComponent* focTrans) { focusTrans = focTrans; prevFocusPos = focusTrans->GetPosition(); }
	void SetSprite(std::string sName, float sWidth, float sHeight) { spriteName = sName; spriteWidth = sWidth; spriteHeight = sHeight; }
	void SetMoveRate(float mRate) { moveRate = mRate; }

private:
	TransformComponent* focusTrans;

	Vec2 prevFocusPos;
	float moveRate;

	std::string spriteName;
	float spriteWidth;
	float spriteHeight;
};