#pragma once

#include "Consts.h"


class QuadTree
{
public:
	QuadTree(int level, Rect bounds);
	~QuadTree();

	void Clear();
	void Split();
	int GetIndex(Rect rect);
	void Insert(Rect rect);
	bool Erase(int colliderIndex);
	bool Erase(int colliderIndex, Rect rect);
	std::vector<int> Retrieve(std::vector<int> &objects, Rect rect);

private:
	int							 _level;
	Rect						 _bounds;
	std::vector<Rect>			 _objects;
	std::vector<QuadTree*>		 _nodes;
};	