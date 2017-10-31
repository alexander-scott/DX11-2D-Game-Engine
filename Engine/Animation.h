#pragma once

#include "Graphics.h"
#include <vector>

class Animation
{
public:
	Animation( int x,int y,int width,int height,int count,const std::string& sprite,float holdTime );

	void Draw( const XMFLOAT2& pos, const float& rot, Graphics& gfx ) const;
	void Update( float dt );

private:
	void Advance();

private:
	const std::string				_fileName;
	std::vector<RECT*>				_animationFrames;
	float							_holdTime;

	int								_currentFrame = 0;
	float							_currentFrameTime = 0.0f;
};