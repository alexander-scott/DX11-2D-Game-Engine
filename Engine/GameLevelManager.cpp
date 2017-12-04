#include "GameLevelManager.h"

using namespace rapidxml;

void GameLevelManager::ExtractLevelData(xml_node<>* root)
{
	//Resize level
	_levelData.levelWidth = atoi(root->first_attribute("width")->value());
	_levelData.levelHeight = atoi(root->first_attribute("height")->value());
	SetDimensions(_levelData.levelWidth, _levelData.levelHeight);

	_levelData.levelLeftBounds = atoi(root->first_attribute("levelLeftBounds")->value());
	_levelData.levelRightBounds = atoi(root->first_attribute("levelRightBounds")->value());

	// Find the player data
	xml_node<>* player = root->first_node("player");
	_levelData.playerXPos = (float)_xOrigin + (atoi(player->first_attribute("x")->value()) * _xStep);
	_levelData.playerYPos = (float)_yOrigin + -(atoi(player->first_attribute("y")->value()) * _yStep);
}
