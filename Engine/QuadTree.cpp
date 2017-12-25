#include "QuadTree.h"



QuadTree::QuadTree(int level, Bounds bounds)
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

	_nodes[0] = new QuadTree(_level + 1, Bounds(x + subWidth, y, subWidth, subHeight));
	_nodes[1] = new QuadTree(_level + 1, Bounds(x, y, subWidth, subHeight));
	_nodes[2] = new QuadTree(_level + 1, Bounds(x, y + subHeight, subWidth, subHeight));
	_nodes[3] = new QuadTree(_level + 1, Bounds(x + subWidth, y + subHeight, subWidth, subHeight));
}

int QuadTree::GetChildNodeIndex(Bounds bounds)
{
	int index = -1;
	double verticalMidpoint = _bounds.xPos + (_bounds.width / 2);
	double horizontalMidpoint = _bounds.yPos + (_bounds.height / 2);

	bool topQuadrant = (bounds.yPos < horizontalMidpoint && bounds.yPos + bounds.height < horizontalMidpoint);
	bool bottomQuadrant = (bounds.yPos > horizontalMidpoint);

	if (bounds.xPos < verticalMidpoint && bounds.xPos + bounds.width < verticalMidpoint)
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
	else if (bounds.xPos > verticalMidpoint)
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

void QuadTree::Insert(Bounds bounds)
{
	if (_nodes[0] != nullptr)
	{
		int index = GetChildNodeIndex(bounds);

		if (index != -1)
		{
			_nodes[index]->Insert(bounds);
			return;
		}
	}

	_objects.push_back(bounds);

	if (_objects.size() > MAX_QUADTREE_OBJECTS && _level < MAX_QUADTREE_LEVELS)
	{
		if (_nodes[0] == nullptr)
		{
			Split();
		}

		int i = 0;
		while (i < _objects.size())
		{
			int index = GetChildNodeIndex(_objects[i]);
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

bool QuadTree::Erase(int colliderIndex, Bounds bounds)
{
	int index = GetChildNodeIndex(bounds);
	if (index != -1 && _nodes[0] != nullptr)
	{
		if (_nodes[index]->Erase(colliderIndex, bounds))
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

std::vector<int> QuadTree::Retrieve(std::vector<int> &objects, Bounds bounds)
{
	int index = GetChildNodeIndex(bounds);
	if (index != -1 && _nodes[0] != nullptr)
	{
		_nodes[index]->Retrieve(objects, bounds);
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


