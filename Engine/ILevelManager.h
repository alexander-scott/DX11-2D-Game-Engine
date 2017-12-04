#pragma once

#include <vector>
#include <fstream>

#include "WorldTile.h"
#include "Consts.h"

#include "rapidxml.hpp"

using namespace rapidxml;

class ILevelManager
{
public:
	void AddTile(int x, int y, WorldTile* tile);
	WorldTile* GetTile(unsigned int x, unsigned int y);

	virtual LevelData GetLevelData() = 0; // THIS SHOULD RETURN ILEVELDATA
	void LoadLevel(std::string filename);

protected:
	virtual void ExtractLevelData(xml_node<>* root) = 0;

	void SetDimensions(int w, int h);

	//A 2D array of Tile pointers
	std::vector<std::vector<WorldTile*>> map;

	int							_xStep;
	int							_yStep;

	int							_xOrigin;
	int							_yOrigin;
};

