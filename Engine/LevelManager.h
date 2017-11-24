#pragma once

#include <vector>
#include <fstream>

#include "WorldTile.h"
#include "Consts.h"

#include "rapidxml.hpp"

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	void AddTile(int x, int y, WorldTile* tile);
	WorldTile* GetTile(unsigned int x, unsigned int y);

	void LoadLevel(std::string filename);

	int GetWidth();
	int GetHeight();

private:
	//A 2D array of Tile pointers
	std::vector<std::vector<WorldTile*>> map;

	//Width and height of level (in tiles)
	int w;
	int h;

	void SetDimensions(int w, int h);
};

