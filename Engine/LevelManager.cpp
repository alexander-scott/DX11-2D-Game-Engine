#include "LevelManager.h"

using namespace rapidxml;

LevelManager::LevelManager()
{
}


LevelManager::~LevelManager()
{
}

void LevelManager::AddTile(int x, int y, WorldTile * tile)
{
	map[x][y] = tile;
}

WorldTile * LevelManager::GetTile(unsigned int x, unsigned int y)
{
	if (x < map.capacity())
	{
		if (y < map[x].capacity())
		{
			return map[x][y];
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

void LevelManager::LoadLevel(std::string filename)
{
	//Loads a level from xml file
	//Load the file
	std::ifstream inFile(filename);

	if (!inFile)
		throw "Could not load tileset: " + filename;

	//Dump contents of file into a string
	std::string xmlContents;

	//Blocked out of preference
	{
		std::string line;
		while (std::getline(inFile, line))
			xmlContents += line;
	}

	//Convert string to rapidxml readable char*
	std::vector<char> xmlData = std::vector<char>(xmlContents.begin(), xmlContents.end());
	xmlData.push_back('\0');

	//Create a parsed document with &xmlData[0] which is the char*
	xml_document<> doc;
	doc.parse<parse_no_data_nodes>(&xmlData[0]);

	//Get the root node
	xml_node<>* root = doc.first_node();

	//Get level attributes
	int width = atoi(root->first_attribute("width")->value());
	int height = atoi(root->first_attribute("height")->value());

	//Resize level
	this->w = width;
	this->h = height;
	SetDimensions(width, height);

	//Go through each tile
	xml_node<>* tile = root->first_node("tile");
	while (tile)
	{
		//Get all the attributes
		int x = atoi(tile->first_attribute("x")->value());
		int y = atoi(tile->first_attribute("y")->value());

		//Create the tile and add it to the level.
		WorldTile* newTile = new WorldTile(std::string(tile->first_attribute("y")->value()), Vec2(x,y));
		AddTile(x, y, newTile);

		//Go to the next tile
		tile = tile->next_sibling("tile");
	}
}

int LevelManager::GetWidth()
{
	return w;
}

int LevelManager::GetHeight()
{
	return h;
}

void LevelManager::SetDimensions(int w, int h)
{
	//w rows
	map.resize(w);

	//Each row has h columns of null Tile pointers
	for (int i = 0; i < w; i++)
	{
		map.at(i).resize(h, 0);
	}
}

