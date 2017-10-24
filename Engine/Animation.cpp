#include "Animation.h"

Animation::Animation( int x,int y,int width,int height,int count,
					  const std::string& sprite,float holdTime )
	:
	_fileName( sprite ),
	_holdTime( holdTime )
{
	for( int i = 0; i < count; i++ )
	{
		RECT* r = new RECT();
		r->left = x + i * width;
		r->right = x + (i + 1) * width;
		r->top = y;
		r->bottom = y + height;

		_animationFrames.emplace_back(r);
	}
}

void Animation::Draw(const XMFLOAT2 & pos, Graphics & gfx) const
{
	gfx.DrawSpriteDX11(_fileName, pos, _animationFrames[_currentFrame]);
}

void Animation::Update( float dt )
{
	_currentFrameTime += dt;
	while( _currentFrameTime >= _holdTime )
	{
		Advance();
		_currentFrameTime -= _holdTime;
	}
}

void Animation::Advance()
{
	if( ++_currentFrame >= _animationFrames.size() )
	{
		_currentFrame = 0;
	}
}
