#pragma once

#include "Graphics.h"

class GUIText
{
public:
	GUIText(std::string text, XMFLOAT2& pos);
	void Draw(Graphics& gfx) const;

private:
	std::string					_text;
	XMFLOAT2					_pos;

};

