#include "GUIText.h"



GUIText::GUIText(std::string text, XMFLOAT2& pos) :
	_pos(pos), _text(text)
{
}

void GUIText::Draw(Graphics & gfx) const
{
	//gfx.DrawTextDX11(_text, _pos);
}
