#pragma once

#include "ICamera.h"
#include "GameObject.h"
#include "ComponentFactory.h"

class GameCamera : public ICamera, public GameObject
{
public:
	GameCamera();
	~GameCamera();

	virtual void Update(float deltaTime) override;

	virtual void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot) override;
	virtual void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot, float scale) override;
	virtual void DrawText(std::string text, Vec2 pos) override;
	virtual void DrawLine(Vec2 v1, Vec2 v2) override;

private:
	TransformComponent* trans;
};

