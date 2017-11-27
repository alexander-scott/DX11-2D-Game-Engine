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

	while (true)
	{
		if (focusTrans->GetPosition().x > 0)
			centreTileXPos = GetTransform()->GetPosition().x + (spriteWidth * count);
		else
			centreTileXPos = GetTransform()->GetPosition().x - (spriteWidth * count);
		xDiffNew = std::abs(centreTileXPos - focusTrans->GetPosition().x);

		if (xDiffNew > xDiffOld)
		{
			if (focusTrans->GetPosition().x > 0)
				centreTileXPos -= spriteWidth/2;
			else
				centreTileXPos += spriteWidth/2;
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

	while (true)
	{
		if (focusTrans->GetPosition().y > 0)
			centreTileYPos = GetTransform()->GetPosition().y + (spriteHeight * count);
		else
			centreTileYPos = GetTransform()->GetPosition().y - (spriteHeight * count);
		yDiffNew = std::abs(centreTileYPos - focusTrans->GetPosition().y);

		if (yDiffNew > yDiffOld)
		{
			if (focusTrans->GetPosition().y > 0)
				centreTileYPos -= spriteHeight / 2;
			else
				centreTileYPos += spriteHeight / 2;
			break;
		}
		else
		{
			count++;
			yDiffOld = yDiffNew;
		}
	}

	// Draw more tiles around the centre tile to get the illusion of a massive background
	for (int i = -2; i < 3; i++) 
	{
		for (int j = -2; j < 3; j++)
		{
			cam->DrawSprite(spriteName, Vec2(centreTileXPos + (i * spriteWidth), centreTileYPos + (j * spriteHeight)), nullptr, 0);
		}
	}
}

void TiledBGRenderer::Update(float deltaTime)
{
	/*Vec2 dist = focusTrans->GetPosition() - prevFocusPos;
	dist.Normalize();
	GetTransform()->SetPosition(GetTransform()->GetPosition() + dist);
	prevFocusPos = focusTrans->GetPosition();*/
}
