#include "GUIText.h"



GUIText::GUIText(std::string text, Vec2 & pos) :
	_pos(pos)
{
	std::wstring widestr = std::wstring(text.begin(), text.end());
	_text = widestr.c_str();
}

void GUIText::Draw(Graphics & gfx) const
{
	gfx.DrawTextDX11(_text);
}
