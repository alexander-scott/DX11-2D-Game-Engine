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
	int							 mLevel;
	Bounds						 mBounds;
	std::vector<Bounds>			 mObjects;
	std::vector<QuadTree*>		 mNodes;
};	