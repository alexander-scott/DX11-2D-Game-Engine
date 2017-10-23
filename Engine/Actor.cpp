#include "Actor.h"
#include "SpriteEffect.h"

Actor::Actor(const Vec2& pos)
	:
	sprite("Images\\link90x90.bmp"),
	pos( pos )
{

}

void Actor::Draw( Graphics& gfx ) const
{
	//gfx.DrawSprite(100, 100, sprite, SpriteEffect::Copy{});
	gfx.DrawSpriteDX11("Images\\windowslogo.dds");
}