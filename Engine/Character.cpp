#include "Character.h"
#include "SpriteEffect.h"

Character::Character( const Vec2& pos )
	:
	sprite( "Images\\link90x90.bmp" ),
	pos( pos )
{

}

void Character::Draw( Graphics& gfx ) const
{
	gfx.DrawSprite(100, 100, sprite, SpriteEffect::Copy{});
}