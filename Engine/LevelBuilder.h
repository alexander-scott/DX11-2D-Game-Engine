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

	inline void UpdateTilePos(xml_node<>* node, shared_ptr<GameObject> obj, LevelData& levelData);
	inline void UpdateColliderBounds(xml_node<>* node, shared_ptr<GameObject> obj, LevelData& levelData);
}