#pragma once

#include "GameObject.h"
#include "ComponentFactory.h"

class Ball : public GameObject
{
public:
	Ball(float xPos, float yPos);
	~Ball();
};

