#include "GameCamera.h"



GameCamera::GameCamera()
{
	gfx = new DX11Graphics();

	trans = ComponentFactory::MakeTransform(Vec2(100, 0), 0, 0);
	AddComponent(trans);
}


GameCamera::~GameCamera()
{
}

void GameCamera::Update(float deltaTime)
{
	Vec2 oldPos = trans->GetPosition();
	oldPos.x += 0.5f;
	trans->SetPosition(oldPos);
}

void GameCamera::DrawSprite(std::string name, Vec2 pos, RECT * rect, float rot)
{
	gfx->DrawSprite(name, pos - trans->GetPosition(), rect, rot);
}

void GameCamera::DrawSprite(std::string name, Vec2 pos, RECT * rect, float rot, float scale)
{
	gfx->DrawSprite(name, pos - trans->GetPosition(), rect, rot, scale);
}

void GameCamera::DrawText(std::string text, Vec2 pos)
{
	gfx->DrawText(text, pos - trans->GetPosition());
}

void GameCamera::DrawLine(Vec2 v1, Vec2 v2)
{
	Vec2 newV1 = v1 - trans->GetPosition();
	Vec2 newV2 = v2 - trans->GetPosition();
	gfx->DrawLine(v1, v2);
}
