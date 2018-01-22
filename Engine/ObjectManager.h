#pragma once

#include <vector>
#include <fstream>

#include "GameObject.h"
#include "GameComponentFactory.h"
#include "Camera.h"

#include "Consts.h"

#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

class ObjectManager
{
public:
	ObjectManager();

	shared_ptr<GameObject> CreateObject(xml_node<>* node, Camera* cam);
	shared_ptr<GameObject> GetCreatedObject(int instanceID);

private:
	IComponent* CreateComponent(shared_ptr<GameObject> go, xml_node<>* node, Camera* cam);
	
	int GenerateNewID();

	map<int, shared_ptr<GameObject>>		mGameObjects;
};

