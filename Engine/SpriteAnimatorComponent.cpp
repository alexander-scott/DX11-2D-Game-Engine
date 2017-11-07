#include "SpriteAnimatorComponent.h"



SpriteAnimatorComponent::SpriteAnimatorComponent()
{
	_type = "Animation";

	for (int i = 0; i < (int)AnimationType::StandingUp; i++) // Add the walking animations - 9 frames
	{
		_animations.emplace_back(Anim(64, 64 * i, 64, 64, 8, 0.16f));
	}
	for (int i = (int)AnimationType::StandingUp; i < (int)AnimationType::Count; i++) // Add the standing animations - 1 frame
	{
		_animations.emplace_back(Anim(0, 64 * (i - (int)AnimationType::StandingUp), 64, 64, 1, 0.16f));
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
