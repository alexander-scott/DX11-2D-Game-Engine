#include "QuadTree.h"



QuadTree::QuadTree(int level, Rect bounds)
{
	_level = level;
	_bounds = bounds;
	_nodes.resize(4);
}


QuadTree::~QuadTree()
{
}

void QuadTree::Clear()
{
	_objects.clear();

	for (int i = 0; i < _nodes.size(); i++)
	{
		if (_nodes[i] != nullptr)
		{
			_nodes[i]->Clear();
			_nodes[i] = nullptr;
		}
	}
}

void QuadTree::Split()
{
	int subWidth = _bounds.width / 2;
	int subHeight = _bounds.height / 2;
	int x = _bounds.xPos;
	int y = _bounds.yPos;

	_nodes[0] = new QuadTree(_level + 1, Rect(x + subWidth, y, subWidth, subHeight));
	_nodes[1] = new QuadTree(_level + 1, Rect(x, y, subWidth, subHeight));
	_nodes[2] = new QuadTree(_level + 1, Rect(x, y + subHeight, subWidth, subHeight));
	_nodes[3] = new QuadTree(_level + 1, Rect(x + subWidth, y + subHeight, subWidth, subHeight));
}

int QuadTree::GetIndex(Rect rect)
{
	int index = -1;
	double verticalMidpoint = _bounds.xPos + (_bounds.width / 2);
	double horizontalMidpoint = _bounds.yPos + (_bounds.height / 2);

	bool topQuadrant = (rect.yPos < horizontalMidpoint && rect.yPos + rect.height < horizontalMidpoint);
	bool bottomQuadrant = (rect.yPos > horizontalMidpoint);

	if (rect.xPos < verticalMidpoint && rect.xPos + rect.width < verticalMidpoint)
	{
		if (topQuadrant)
		{
			index = 1;
		}
		else if (bottomQuadrant)
		{
			index = 2;
		}
	}
	else if (rect.xPos > verticalMidpoint)
	{
		if (topQuadrant)
		{
			index = 0;
		}
		else if (bottomQuadrant)
		{
			index = 3;
		}
	}

	return index;
}

void QuadTree::Insert(Rect rect)
{
	if (_nodes[0] != nullptr)
	{
		int index = GetIndex(rect);

		if (index != -1)
		{
			_nodes[index]->Insert(rect);
			return;
		}
	}

	_objects.push_back(rect);

	if (_objects.size() > MAX_QUADTREE_OBJECTS && _level < MAX_QUADTREE_LEVELS)
	{
		if (_nodes[0] == nullptr)
		{
			Split();
		}

		int i = 0;
		while (i < _objects.size())
		{
			int index = GetIndex(_objects[i]);
			if (index != -1)
			{
				_nodes[index]->Insert(_objects[i]);
				_objects.erase(_objects.begin() + i);
			}
			else
			{
				i++;
			}
		}
	}
}

bool QuadTree::Erase(int colliderIndex)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		if (_objects[i].colliderIndex == colliderIndex)
		{
			_objects.erase(_objects.begin() + i);
			return true;
		}
	}

	for (int i = 0; i < _nodes.size(); i++)
	{
		if (_nodes[i] != nullptr)
			return _nodes[i]->Erase(colliderIndex);
	}

	return false;
}

bool QuadTree::Erase(int colliderIndex, Rect rect)
{
	int index = GetIndex(rect);
	if (index != -1 && _nodes[0] != nullptr)
	{
		if (_nodes[index]->Erase(colliderIndex, rect))
			return true;
	}

	for (int i = 0; i < _objects.size(); i++)
	{
		if (_objects[i].colliderIndex == colliderIndex)
		{
			_objects.erase(_objects.begin() + i);
			return true;
		}
	}

	return false;
}

std::vector<int> QuadTree::Retrieve(std::vector<int> &objects, Rect rect)
{
	int index = GetIndex(rect);
	if (index != -1 && _nodes[0] != nullptr)
	{
		_nodes[index]->Retrieve(objects, rect);
	}

	for (int i = 0; i < _objects.size(); i++)
	{
		if (_objects[i].colliderIndex != -1)
		{
			objects.push_back(_objects[i].colliderIndex);
		}
	}

	return objects;
}


