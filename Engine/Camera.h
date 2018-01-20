#pragma once

#include "ICamera.h"
#include "GameObject.h"
#include "GameComponentFactory.h"

class Camera : public ICamera, public GameObject
{
public:
	Camera();
	~Camera();

	Vec2 GetPosition() { return mTransform->GetPosition(); }

	void DrawSpriteScreenSpace(std::string name, Vec2 pos, RECT* rect, float rot, float scale, Vec2 offset) override;
	void DrawSpriteWorldSpace(std::string name, Vec2 pos, RECT* rect, float rot, float scale, Vec2 offset) override;

	void DrawTextScreenSpace(std::string text, Vec2 pos, float rot, float* rgb, float scale, Vec2 offset) override;
	void DrawTextWorldSpace(std::string text, Vec2 pos, float rot, float* rgb, float scale, Vec2 offset) override;

	virtual void DrawLine(Vec2 v1, Vec2 v2) override;

	static Camera& Instance()
	{
		static Camera Instance;
		return Instance;
	}

protected:
	TransformComponent*		mTransform;
};

