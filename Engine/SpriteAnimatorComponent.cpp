#include "SpriteAnimatorComponent.h"


SpriteAnimatorComponent::SpriteAnimatorComponent(int renderLayer)
{
	RenderLayer = renderLayer;
	mType = "Sprite Animator";
}


SpriteAnimatorComponent::~SpriteAnimatorComponent()
{

}

void SpriteAnimatorComponent::Draw(ICamera* cam)
{
	TransformComponent* trans = GetTransform();

	float halfSpriteWidth = (mSpriteWidth / 2) * trans->GetWorldScale();
	float halfSpriteHeight = (mSpriteHeight / 2) * trans->GetWorldScale();

	Vec2 pos = trans->GetWorldPosition();
	float newPosX = pos.x
		- halfSpriteWidth * cos(trans->GetWorldRotation())
		+ halfSpriteHeight * sin(trans->GetWorldRotation());

	float newPosY = pos.y
		- halfSpriteHeight * cos(trans->GetWorldRotation())
		- halfSpriteWidth * sin(trans->GetWorldRotation());

	cam->DrawSpriteWorldSpace(mSpriteFileName, Vec2(newPosX, newPosY), 
		mAnimations[(int)mSequenceIndex].AnimationFrames[mAnimations[(int)mSequenceIndex].CurrentFrame], 
		GetTransform()->GetWorldRotation(), GetTransform()->GetWorldScale(), Vec2(0,0));
}

void SpriteAnimatorComponent::Update(float deltaTime)
{
	mAnimations[(int)mSequenceIndex].Advance(deltaTime);
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
	mSequenceIndex = currentAnim;

	for (auto& animDesc : animDescs)
	{
		for (int i = animDesc.StartingIndex; i < animDesc.EndingIndex; i++)
		{
			mAnimations.emplace_back(Anim(animDesc.X, animDesc.Y * (i - animDesc.StartingIndex), animDesc.Width, animDesc.Height, animDesc.FrameCount, animDesc.HoldTime));
		}
	}
}

void SpriteAnimatorComponent::UpdateAnimationSequence(int sequence)
{
	mSequenceIndex = sequence;
}
