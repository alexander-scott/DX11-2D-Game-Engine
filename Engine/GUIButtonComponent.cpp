#include "GUIButtonComponent.h"

GUIButtonComponent::GUIButtonComponent(TransformComponent* trans, float width, float height) : mTransform(trans), mWidth(width), mHeight(height)
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
		Rect buttonRect;
		buttonRect.LeftX = (int)(mTransform->GetPosition().x - (mWidth / 2));
		buttonRect.RightX = (int)(mTransform->GetPosition().x + (mWidth / 2));
		buttonRect.BotY = (int)(mTransform->GetPosition().y - (mHeight / 2));
		buttonRect.TopY = (int)(mTransform->GetPosition().y + (mHeight / 2));

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
