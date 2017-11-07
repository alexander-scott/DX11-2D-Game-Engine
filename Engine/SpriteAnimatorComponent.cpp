#include "SpriteAnimatorComponent.h"
#include "UpdateDirectionMessage.h"


SpriteAnimatorComponent::SpriteAnimatorComponent(std::vector<AnimationDesc> animDescs)
{
	_type = "Animation";

	for (auto animDesc : animDescs)
	{
		for (int i = animDesc.StartingIndex; i < animDesc.EndingIndex; i++)
		{
			_animations.emplace_back(Anim(animDesc.X, animDesc.Y * (i - animDesc.StartingIndex), animDesc.Width, animDesc.Height, animDesc.FrameCount, animDesc.HoldTime));
		}
	}
}


SpriteAnimatorComponent::~SpriteAnimatorComponent()
{

}

void SpriteAnimatorComponent::Draw(Graphics & gfx)
{
	gfx.DrawSpriteDX11(_fileName, GetTransform()->GetPosition(), _animations[(int)iCurSequence]._animationFrames[_animations[(int)iCurSequence]._currentFrame], GetTransform()->GetRotation());
}

void SpriteAnimatorComponent::Update(float deltaTime)
{
	_animations[(int)iCurSequence].Advance(deltaTime);
}

void SpriteAnimatorComponent::RecieveMessage(IMessage & message)
{
	switch (message.GetType())
	{
		case MessageType::UpdateDirection:
			UpdateDirectionMessage& addForceMsg = static_cast<UpdateDirectionMessage &> (message);
			UpdateDirection(addForceMsg.GetDir());
			break;
	}
}

void SpriteAnimatorComponent::UpdateDirection(Vec2 dir)
{
	if (dir.x > 0.0f)
	{
		iCurSequence = AnimationType::WalkingRight;
	}
	else if (dir.x < 0.0f)
	{
		iCurSequence = AnimationType::WalkingLeft;
	}
	else if (dir.y < 0.0f)
	{
		iCurSequence = AnimationType::WalkingUp;
	}
	else if (dir.y > 0.0f)
	{
		iCurSequence = AnimationType::WalkingDown;
	}
}
