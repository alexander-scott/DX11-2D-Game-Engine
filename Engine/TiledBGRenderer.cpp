#include "TiledBGRenderer.h"



TiledBGRenderer::TiledBGRenderer()
{
}


TiledBGRenderer::~TiledBGRenderer()
{
}

void TiledBGRenderer::Draw(ICamera * cam)
{
	// Find closest tile centre to focusTrans
	// Find X and Y indivudally
	// Multiply trans.x by spriteWidth. Store the difference between newX and focusTrans.x. Loop until the new difference is greater than the old difference.
	// Repeat for Y
	// Around this central tile draw 8 more tiles around it by adding/subtracing spriteWidth and spriteHeight

	float centreTileXPos;
	float xDiffOld = 10000000;
	float xDiffNew = 0;
	int count = 0;

	// Find the closest X centre
	while (true)
	{
		if (_focusTrans->GetPosition().x > 0)
			centreTileXPos = GetTransform()->GetPosition().x + (_spriteWidth * count);
		else
			centreTileXPos = GetTransform()->GetPosition().x - (_spriteWidth * count);
		xDiffNew = std::abs(centreTileXPos - _focusTrans->GetPosition().x);

		if (xDiffNew > xDiffOld)
		{
			if (_focusTrans->GetPosition().x > 0)
				centreTileXPos -= _spriteWidth/2;
			else
				centreTileXPos += _spriteWidth/2;
			break;
		}
		else 
		{
			count++;
			xDiffOld = xDiffNew;
		}
	}

	float centreTileYPos;
	float yDiffOld = 10000000;
	float yDiffNew = 0;
	count = 0;

	// Find the closest Y centre
	while (true)
	{
		if (_focusTrans->GetPosition().y > 0)
			centreTileYPos = GetTransform()->GetPosition().y + (_spriteHeight * count);
		else
			centreTileYPos = GetTransform()->GetPosition().y - (_spriteHeight * count);
		yDiffNew = std::abs(centreTileYPos - _focusTrans->GetPosition().y);

		if (yDiffNew > yDiffOld)
		{
			if (_focusTrans->GetPosition().y > 0)
				centreTileYPos -= _spriteHeight / 2;
			else
				centreTileYPos += _spriteHeight / 2;
			break;
		}
		else
		{
			count++;
			yDiffOld = yDiffNew;
		}
	}

	switch (_scrollDir)
	{
		case TiledBGDirection::eHorizontal:
			for (int i = -2; i < 3; i++)
			{
				cam->DrawSprite(_spriteName, Vec2(centreTileXPos + (i * _spriteWidth), GetTransform()->GetPosition().y), nullptr, 0);
			}
			break;

		case TiledBGDirection::eVertical:
			for (int i = -2; i < 3; i++)
			{
				cam->DrawSprite(_spriteName, Vec2(GetTransform()->GetPosition().x, centreTileYPos + (i * _spriteHeight)), nullptr, 0);
			}
			break;

		case TiledBGDirection::eHoriztonalAndVertical:
			// Draw more tiles around the centre tile to get the illusion of a massive background
			for (int i = -2; i < 3; i++)
			{
				for (int j = -2; j < 3; j++)
				{
					cam->DrawSprite(_spriteName, Vec2(centreTileXPos + (i * _spriteWidth), centreTileYPos + (j * _spriteHeight)), nullptr, 0);
				}
			}
			break;
	}
}

void TiledBGRenderer::Update(float deltaTime)
{
	Vec2 dist = _focusTrans->GetPosition() - _prevFocusPos;
	float length = dist.Len();
	if (length < 1)
	{
		return; // If the movement is so small, just return as the background will move too fast
	}

	dist.Normalize();

	switch (_scrollDir)
	{
		case TiledBGDirection::eHorizontal:
			dist.y = 0;
			break;

		case TiledBGDirection::eVertical:
			dist.x = 0;
			break;
	}

	GetTransform()->SetPosition(GetTransform()->GetPosition() - (dist * _scrollRate));
	_prevFocusPos = _focusTrans->GetPosition();
}
