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
	void Initalise(std::string fileName);
	void SetCamera(GameCamera* cam)	{ mCamera = cam; }

	GameObject* CreateObject(int instanceID, int blueprintID);
	GameObject* GetCreatedObject(int instanceID);

private:
	IComponent* CreateComponent(GameObject* go, xml_node<>* node);

	GameCamera*							mCamera;

	std::map<int, GameObject*>			mGameObjects;
	std::string							mfileName = "Levels\\GameValues.xml";
};

