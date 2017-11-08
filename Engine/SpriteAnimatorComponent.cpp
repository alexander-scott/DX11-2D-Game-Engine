#include "SpriteAnimatorComponent.h"
#include "UpdateDirectionMessage.h"


SpriteAnimatorComponent::SpriteAnimatorComponent()
{
	_type = "Animation";
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
	/*switch (message.GetType())
	{
		case MessageType::UpdateDirection:
			UpdateDirectionMessage& updateDirMsg = static_cast<UpdateDirectionMessage &> (message);
			UpdateAnimationSequence(updateDirMsg.GetDir());
			break;
	}*/
}

void SpriteAnimatorComponent::SetAnimations(int currentAnim, std::vector<AnimationDesc> animDescs)
{
	iCurSequence = currentAnim;

	for (auto animDesc : animDescs)
	{
		for (int i = animDesc.StartingIndex; i < animDesc.EndingIndex; i++)
		{
			_animations.emplace_back(Anim(animDesc.X, animDesc.Y * (i - animDesc.StartingIndex), animDesc.Width, animDesc.Height, animDesc.FrameCount, animDesc.HoldTime));
		}
	}
}

void SpriteAnimatorComponent::UpdateAnimationSequence(int sequence)
{
	iCurSequence = sequence;
}
