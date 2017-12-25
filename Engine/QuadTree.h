#pragma once

#include "Consts.h"


class QuadTree
{
public:
	QuadTree(int level, Bounds bounds);
	~QuadTree();

	void Clear();
	void Split();
	int GetChildNodeIndex(Bounds bounds);
	void Insert(Bounds bounds);
	bool Erase(int colliderIndex);
	bool Erase(int colliderIndex, Bounds bounds);
	std::vector<int> Retrieve(std::vector<int> &objects, Bounds bounds);

private:
	int							 _level;
	Bounds						 _bounds;
	std::vector<Bounds>			 _objects;
	std::vector<QuadTree*>		 _nodes;
};	