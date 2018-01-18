#pragma once

#include "IComponent.h"
#include "IDrawable.h"
#include "IUpdateable.h"

#include "IMessageable.h"
#include "UpdateAnimationSequenceMessage.h"

#include "Consts.h"

#include "SpriteRendererComponent.h"
#include <vector>

class SpriteAnimatorComponent : public IComponent, public IDrawable, public IUpdateable, public IMessageable
{
public:
	struct Anim
	{
	public:
		Anim(int x, int y, int width, int height, int count, float holdTime) :
			mHoldTime(holdTime)
		{
			for (int i = 0; i < count; i++)
			{
				RECT* r = new RECT();
				r->left = x + i * width;
				r->right = x + (i + 1) * width;
				r->top = y;
				r->bottom = y + height;

				AnimationFrames.emplace_back(r);
			}
		}

		void Advance(float dt)
		{
			mCurrentFrameTime += dt;
			while (mCurrentFrameTime >= mHoldTime)
			{
				if (++CurrentFrame >= AnimationFrames.size())
				{
					CurrentFrame = 0;
				}

				mCurrentFrameTime -= mHoldTime;
			}
		}

		std::vector<RECT*>				AnimationFrames;
		int								CurrentFrame = 0;

	private:
		float							mHoldTime;
		float							mCurrentFrameTime = 0.0f;

	};

	SpriteAnimatorComponent(int renderLayer);
	~SpriteAnimatorComponent();

	virtual void Draw(ICamera* cam) override;
	virtual void Update(float deltaTime) override;
	virtual void RecieveMessage(IMessage& message) override;

	void SetFilename(std::string fileName) { mSpriteFileName = fileName; }
	void SetAnimations(int currentAnim, std::vector<AnimationDesc> animDescs);
	void SetWidthHeight(float wid, float hei) { mSpriteWidth = wid; mSpriteHeight = hei; }

private:
	void UpdateAnimationSequence(int sequence);

	int								mSequenceIndex;
	std::vector<Anim>				mAnimations;
	std::string						mSpriteFileName;

	float							mSpriteWidth;
	float							mSpriteHeight;
};

