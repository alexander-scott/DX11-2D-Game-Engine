#pragma once

#include <vector>
#include <fstream>

#include "WorldTile.h"
#include "Consts.h"

#include "rapidxml.hpp"

class LevelManager
{
public:
	LevelManager(int xstep, int ystep, int xorigin, int yorigin) : _xStep(xstep), _yStep(ystep), _xOrigin(xorigin), _yOrigin(yorigin) { }
	~LevelManager();

	void AddTile(int x, int y, WorldTile* tile);
	WorldTile* GetTile(unsigned int x, unsigned int y);

	void LoadLevel(std::string filename);

	int GetWidth();
	int GetHeight();

private:
	void SetDimensions(int w, int h);

	//A 2D array of Tile pointers
	std::vector<std::vector<WorldTile*>> map;

	//Width and height of level (in tiles)
	int									_width;
	int									_height;

	int									_xStep;
	int									_yStep;

	int									_xOrigin;
	int									_yOrigin;
};

