#include "Animation.h"

Animation::Animation( int x,int y,int width,int height,int count,
					  const std::string& sprite,float holdTime )
	:
	fileName( sprite ),
	holdTime( holdTime )
{
	for( int i = 0; i < count; i++ )
	{
		RECT* r = new RECT();
		r->left = x + i * width;
		r->right = x + (i + 1) * width;
		r->top = y;
		r->bottom = y + height;

		frames.emplace_back(r);
	}
}

void Animation::Draw(const XMFLOAT2 & pos, Graphics & gfx) const
{
	gfx.DrawSpriteDX11(fileName, pos, frames[iCurFrame]);
}

void Animation::Update( float dt )
{
	curFrameTime += dt;
	while( curFrameTime >= holdTime )
	{
		Advance();
		curFrameTime -= holdTime;
	}
}

void Animation::Advance()
{
	if( ++iCurFrame >= frames.size() )
	{
		iCurFrame = 0;
	}
}
