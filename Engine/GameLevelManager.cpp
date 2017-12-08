#include "GameLevelManager.h"

using namespace rapidxml;

void GameLevelManager::ExtractLevelData(xml_node<>* root)
{
	//Resize level
	_levelData.levelWidth = atoi(root->first_attribute("width")->value());
	_levelData.levelHeight = atoi(root->first_attribute("height")->value());
	SetDimensions(_levelData.levelWidth, _levelData.levelHeight);

	_levelData.levelLeftBounds = (float)atoi(root->first_attribute("levelLeftBounds")->value());
	_levelData.levelRightBounds = (float)atoi(root->first_attribute("levelRightBounds")->value());

	_levelData.levelBottomBounds = (float)atoi(root->first_attribute("levelBottomBounds")->value());
	_levelData.levelTopBounds = (float)atoi(root->first_attribute("levelTopBounds")->value());

	// Find the player data
	xml_node<>* player = root->first_node("player");
	_levelData.playerXPos = (float)_xOrigin + (atoi(player->first_attribute("x")->value()) * _xStep);
	_levelData.playerYPos = (float)_yOrigin + -(atoi(player->first_attribute("y")->value()) * _yStep);
}
