#pragma once

#include "IComponent.h"
#include "IDrawable.h"
#include "IUpdateable.h"
#include "IMessageable.h"

#include "Consts.h"

#include "SpriteRendererComponent.h"
#include <vector>

class SpriteAnimatorComponent : public IComponent, public IDrawable, public IUpdateable, public IMessageable
{
public:
	struct Anim
	{
		std::vector<RECT*>				_animationFrames;
		float							_holdTime;

		int								_currentFrame = 0;
		float							_currentFrameTime = 0.0f;

		Anim(int x, int y, int width, int height, int count, float holdTime) :
			_holdTime(holdTime)
		{
			for (int i = 0; i < count; i++)
			{
				RECT* r = new RECT();
				r->left = x + i * width;
				r->right = x + (i + 1) * width;
				r->top = y;
				r->bottom = y + height;

				_animationFrames.emplace_back(r);
			}
		}

		void Advance(float dt)
		{
			_currentFrameTime += dt;
			while (_currentFrameTime >= _holdTime)
			{
				if (++_currentFrame >= _animationFrames.size())
				{
					_currentFrame = 0;
				}

				_currentFrameTime -= _holdTime;
			}
		}
	};

	SpriteAnimatorComponent(std::vector<AnimationDesc> animDescs);
	~SpriteAnimatorComponent();

	virtual void Draw(Graphics& gfx) override;
	virtual void Update(float deltaTime) override;
	virtual void RecieveMessage(IMessage & message) override;

	void SetFilename(std::string fileName) { _fileName = fileName; }
	void UpdateDirection(Vec2 dir);

private:
	AnimationType iCurSequence = AnimationType::WalkingDown;
	std::vector<Anim>				_animations;
	std::string						_fileName;
};

