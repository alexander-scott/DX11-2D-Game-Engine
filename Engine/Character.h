#pragma once

#include "Surface.h"
#include "Graphics.h"
#include "Vec2.h"

class Character
{
private:

public:
	Character( const Vec2& pos );
	void Draw( Graphics& gfx ) const;

private:
	Surface sprite;
	Vec2 pos;
};