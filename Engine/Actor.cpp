#include "Actor.h"

Actor::Actor(const Vec2& pos)
	:
	pos( pos )
{

}

void Actor::Draw( Graphics& gfx ) const
{
	gfx.DrawSpriteDX11("Images\\windowslogo.dds");
}