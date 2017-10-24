#pragma once

#include "Graphics.h"
#include <vector>

class Animation
{
public:
	Animation( int x,int y,int width,int height,int count,const std::string& sprite,float holdTime );
	void Draw( const XMFLOAT2& pos,Graphics& gfx ) const;
	void Update( float dt );
private:
	void Advance();
private:
	const std::string fileName;
	std::vector<RECT*> frames;
	int iCurFrame = 0;
	float holdTime;
	float curFrameTime = 0.0f;
};