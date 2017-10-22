#pragma once

#include "Surface.h"
#include "Graphics.h"
#include "Vec2.h"

class Actor
{
private:

public:
	Actor( const Vec2& pos );
	void Draw( Graphics& gfx ) const;

private:
	Surface sprite;
	Vec2 pos;
};