#include "GUIButtonComponent.h"



GUIButtonComponent::GUIButtonComponent(PolygonColliderComponent* collider) : mCollider(collider)
{
	mClicked = false; 
	mIsPressed = false;
}


GUIButtonComponent::~GUIButtonComponent()
{
}

void GUIButtonComponent::Update(float deltaTime)
{
	if (mClicked)
		return;

	if (Mouse::Instance().LeftIsPressed() && !mIsPressed)
	{
		mIsPressed = true;

		Vec2 mousePos = Mouse::Instance().GetPos();
		Rect buttonRect = mCollider->GetRect();

		if (buttonRect.LeftX < mousePos.x && buttonRect.RightX > mousePos.x && buttonRect.BotY < mousePos.y && buttonRect.TopY > mousePos.y)
		{
			mClicked = true;
		}
	}
	else if (!Mouse::Instance().LeftIsPressed())
	{
		mIsPressed = false;
	}
}
