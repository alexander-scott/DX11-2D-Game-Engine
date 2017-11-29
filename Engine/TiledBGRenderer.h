#pragma once

#include "IComponent.h"
#include "IDrawable.h"
#include "IUpdateable.h"
#include "TransformComponent.h"

#include <vector>

class TiledBGRenderer : public IComponent, public IDrawable, public IUpdateable
{
public:
	TiledBGRenderer();
	~TiledBGRenderer();

	virtual void Draw(ICamera* cam) override;
	virtual void Update(float deltaTime) override;

	void SetFocusTrans(TransformComponent* focTrans) { _focusTrans = focTrans; _prevFocusPos = _focusTrans->GetPosition(); }
	void SetSprite(std::string sName, float sWidth, float sHeight) { _spriteName = sName; _spriteWidth = sWidth; _spriteHeight = sHeight; }
	void SetMoveRate(float mRate) { _moveRate = mRate; }
	void SetDirection(TiledBGDirection dir) { _scrollDir = dir; }

private:
	TransformComponent*					_focusTrans;

	Vec2								_prevFocusPos;
	float								_moveRate;

	TiledBGDirection					_scrollDir;

	std::string							_spriteName;
	float								_spriteWidth;
	float								_spriteHeight;
};