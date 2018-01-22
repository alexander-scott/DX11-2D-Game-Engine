#pragma once

#include "IScene.h"
#include "ObjectManager.h"

#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

namespace SceneBuilder
{
	void InitaliseGameplayValues(string fileName);

	void BuildScene(shared_ptr<IScene> scene, string fileName);

	inline LevelData ExtractLevelData(xml_node<>* node);
}