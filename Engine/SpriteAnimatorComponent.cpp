#include "SpriteAnimatorComponent.h"


SpriteAnimatorComponent::SpriteAnimatorComponent()
{
	_type = "Sprite Animator";
}


SpriteAnimatorComponent::~SpriteAnimatorComponent()
{

}

void SpriteAnimatorComponent::Draw(ICamera* cam)
{
	TransformComponent* trans = GetTransform();

	float halfSpriteWidth = (_spriteWidth / 2) * trans->GetScale();
	float halfSpriteHeight = (_spriteHeight / 2) * trans->GetScale();

	Vec2 pos = trans->GetPosition();
	float newPosX = pos.x
		- halfSpriteWidth * cos(trans->GetRotation())
		+ halfSpriteHeight * sin(trans->GetRotation());

	float newPosY = pos.y
		- halfSpriteHeight * cos(trans->GetRotation())
		- halfSpriteWidth * sin(trans->GetRotation());

	cam->DrawSprite(_fileName, Vec2(newPosX, newPosY), _animations[(int)iCurSequence]._animationFrames[_animations[(int)iCurSequence]._currentFrame], GetTransform()->GetRotation(), GetTransform()->GetScale());
}

void SpriteAnimatorComponent::Update(float deltaTime)
{
	_animations[(int)iCurSequence].Advance(deltaTime);
}

void SpriteAnimatorComponent::RecieveMessage(IMessage & message)
{
	switch (message.GetType())
	{
		case MessageType::eUpdateAnimationSequence:
			UpdateAnimationSequenceMessage& updateSeqMsg = static_cast<UpdateAnimationSequenceMessage &> (message);
			UpdateAnimationSequence(updateSeqMsg.GetSequence());
			break;
	}
}

void SpriteAnimatorComponent::SetAnimations(int currentAnim, std::vector<AnimationDesc> animDescs)
{
	iCurSequence = currentAnim;

	for (auto& animDesc : animDescs)
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
