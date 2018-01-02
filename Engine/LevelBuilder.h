#pragma once

#include "GameLevel.h"

#include "rapidxml.hpp"

using namespace rapidxml;

namespace LevelBuilder
{
	void InitaliseGameplayValues(std::string fileName);

	GameLevel* BuildGameLevel(std::string fileName);

	inline LevelData& ExtractLevelData(xml_node<>* node);

	inline void UpdateTilePos(xml_node<>* node, GameObject* obj, LevelData& levelData);
	inline void UpdateColliderBounds(xml_node<>* node, GameObject* obj, LevelData& levelData);
}

