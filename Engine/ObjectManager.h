#pragma once

#include <vector>
#include <fstream>

#include "GameObject.h"
#include "GameComponentFactory.h"
#include "GameCamera.h"

#include "Consts.h"

#include "rapidxml.hpp"

using namespace rapidxml;

class ObjectManager
{
public:
	GameObject* CreateObject(int instanceID, int prefabID);
	GameObject* GetCreatedObject(int instanceID);

private:
	IComponent* CreateComponent(GameObject* go, xml_node<>* node);

	std::map<int, GameObject*>			mGameObjects;
	std::string							mfileName = "Levels\\Prefabs.xml";
};

