#pragma once

#include "ICamera.h"
#include "GameObject.h"
#include "GameComponentFactory.h"

class GameCamera : public ICamera, public GameObject
{
public:
	GameCamera();
	~GameCamera();

	Vec2 GetPosition() { return mTransform->GetPosition(); }

	void SetFocusTrans(TransformComponent* fTrans) { mFocusTrans = fTrans; }
	void SetLevelBounds(float leftBound, float rightBound, float botBound, float topBound) 
	{ mLevelLeftBound = leftBound; mLevelRightBound = rightBound; mLevelBottomBound = botBound; mLevelTopBound = topBound; }

	virtual void Initalise(class MainWindow& wnd) override;

	virtual void Update(float deltaTime) override;

	virtual void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot, float scale, Vec2 offset) override;

	virtual void DrawTextScreenSpace(std::string text, Vec2 pos, float rot, float* rgb, float scale) override;
	virtual void DrawTextWorldSpace(std::string text, Vec2 pos, float rot, float* rgb, float scale) override;

	virtual void DrawLine(Vec2 v1, Vec2 v2) override;

	static GameCamera& Instance()
	{
		static GameCamera Instance;
		return Instance;
	}

private:
	TransformComponent*		mTransform;
	TransformComponent*		mFocusTrans;

	float					mLevelLeftBound;
	float					mLevelRightBound;

	float					mLevelBottomBound;
	float					mLevelTopBound;
};

