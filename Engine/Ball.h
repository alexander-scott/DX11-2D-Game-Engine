#pragma once

#include "GameObject.h"
#include "ComponentFactory.h"

class Ball : public GameObject
{
public:
	Ball(std::string tag, float xPos, float yPos);
	~Ball();
};

