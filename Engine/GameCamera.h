#pragma once

#include "ICamera.h"
#include "GameObject.h"
#include "GameComponentFactory.h"

class GameCamera : public ICamera, public GameObject
{
public:
	GameCamera();
	~GameCamera();

	void SetFocusTrans(TransformComponent* fTrans) { focusTrans = fTrans; }
	void SetLevelBounds(float leftBound, float rightBound, float botBound, float topBound) 
	{ _levelLeftBound = leftBound; _levelRightBound = rightBound; _levelBottomBound = botBound; _levelTopBound = topBound; }

	virtual void Initalise(class MainWindow& wnd) override;

	virtual void Update(float deltaTime) override;

	virtual void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot) override;
	virtual void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot, float scale) override;
	virtual void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot, float scale, Vec2 offset) override;
	virtual void DrawText(std::string text, Vec2 pos) override;
	virtual void DrawLine(Vec2 v1, Vec2 v2) override;

	static GameCamera& Instance()
	{
		static GameCamera Instance;
		return Instance;
	}

private:
	TransformComponent* trans;
	TransformComponent* focusTrans;

	float					_levelLeftBound;
	float					_levelRightBound;

	float					_levelBottomBound;
	float					_levelTopBound;
};

