#pragma once

#include "ILevelManager.h"

#include "rapidxml.hpp"

using namespace rapidxml;

class GameLevelManager : public ILevelManager
{
public:
	GameLevelManager(int xstep, int ystep, int xorigin, int yorigin)
	{
		_xStep = xstep;
		_yStep = ystep;
		_xOrigin = xorigin;
		_yOrigin = yorigin;
	}

	virtual LevelData GetLevelData() override { return _levelData; }

protected:
	virtual void ExtractLevelData(xml_node<>* root) override;

private:
	LevelData _levelData;
};

