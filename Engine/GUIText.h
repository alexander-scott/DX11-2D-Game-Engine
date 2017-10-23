#pragma once

#include "Vec2.h"
#include "Graphics.h"

class GUIText
{
public:
	GUIText(std::string text, Vec2& pos);
	void Draw(Graphics& gfx) const;

private:
	const wchar_t* _text;
	Vec2 _pos;

};

