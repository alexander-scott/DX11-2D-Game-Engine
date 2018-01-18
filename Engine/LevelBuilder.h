#pragma once

#include "GameLevel.h"

#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

namespace LevelBuilder
{
	void InitaliseGameplayValues(string fileName);

	shared_ptr<GameLevel> BuildGameLevel(string fileName, float startScore);

	inline LevelData ExtractLevelData(xml_node<>* node);
}