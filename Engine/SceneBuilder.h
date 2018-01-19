#pragma once

#include "Scene.h"

#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

namespace SceneBuilder
{
	void InitaliseGameplayValues(string fileName);

	shared_ptr<Scene> BuildScene(string fileName);

	inline LevelData ExtractLevelData(xml_node<>* node);
}