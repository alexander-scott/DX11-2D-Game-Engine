#pragma once

#include "GameObject.h"
#include "ComponentFactory.h"

class WorldTile  : public GameObject
{
public:
	WorldTile(std::string fileName, Vec2 pos);
};
