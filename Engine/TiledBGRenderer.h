#pragma once

#include "IComponent.h"
#include "IDrawable.h"
#include "IUpdateable.h"
#include "TransformComponent.h"

#include <vector>

class TiledBGRenderer : public IComponent, public IDrawable, public IUpdateable
{
public:
	TiledBGRenderer(int renderLayer);
	~TiledBGRenderer();

	virtual void Draw(ICamera* cam) override;
	virtual void Update(float deltaTime) override;

	void SetFocusTrans(TransformComponent* focTrans) { mFocusTrans = focTrans; mPrevFocusPos = mFocusTrans->GetWorldPosition(); }
	void SetSprite(std::string sName, float sWidth, float sHeight) { mSpriteFileName = sName; mSpriteWidth = sWidth; mSpriteHeight = sHeight; }
	void SetScrollRate(float mRate) { mScrollRate = mRate; }
	void SetDirection(TiledBGDirection dir) { mScrollDir = dir; }

private:
	TransformComponent*					mFocusTrans;

	Vec2								mPrevFocusPos;
	float								mScrollRate;

	TiledBGDirection					mScrollDir;

	std::string							mSpriteFileName;
	float								mSpriteWidth;
	float								mSpriteHeight;
};