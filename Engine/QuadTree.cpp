#include "QuadTree.h"



QuadTree::QuadTree(int level, Bounds bounds)
{
	mLevel = level;
	mBounds = bounds;
	mNodes.resize(4);
}


QuadTree::~QuadTree()
{
}

void QuadTree::Clear()
{
	mObjects.clear();

	for (int i = 0; i < mNodes.size(); i++)
	{
		if (mNodes[i] != nullptr)
		{
			mNodes[i]->Clear();
			mNodes[i] = nullptr;
		}
	}
}

void QuadTree::Split()
{
	int subWidth = mBounds.width / 2;
	int subHeight = mBounds.height / 2;
	int x = mBounds.xPos;
	int y = mBounds.yPos;

	mNodes[0] = new QuadTree(mLevel + 1, Bounds(x + subWidth, y, subWidth, subHeight));
	mNodes[1] = new QuadTree(mLevel + 1, Bounds(x, y, subWidth, subHeight));
	mNodes[2] = new QuadTree(mLevel + 1, Bounds(x, y + subHeight, subWidth, subHeight));
	mNodes[3] = new QuadTree(mLevel + 1, Bounds(x + subWidth, y + subHeight, subWidth, subHeight));
}

int QuadTree::GetChildNodeIndex(Bounds bounds)
{
	int index = -1;
	double verticalMidpoint = mBounds.xPos + (mBounds.width / 2);
	double horizontalMidpoint = mBounds.yPos + (mBounds.height / 2);

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
	if (mNodes[0] != nullptr)
	{
		int index = GetChildNodeIndex(bounds);

		if (index != -1)
		{
			mNodes[index]->Insert(bounds);
			return;
		}
	}

	mObjects.push_back(bounds);

	if (mObjects.size() > MAX_QUADTREE_OBJECTS && mLevel < MAX_QUADTREE_LEVELS)
	{
		if (mNodes[0] == nullptr)
		{
			Split();
		}

		int i = 0;
		while (i < mObjects.size())
		{
			int index = GetChildNodeIndex(mObjects[i]);
			if (index != -1)
			{
				mNodes[index]->Insert(mObjects[i]);
				mObjects.erase(mObjects.begin() + i);
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
	for (int i = 0; i < mObjects.size(); i++)
	{
		if (mObjects[i].colliderIndex == colliderIndex)
		{
			mObjects.erase(mObjects.begin() + i);
			return true;
		}
	}

	for (int i = 0; i < mNodes.size(); i++)
	{
		if (mNodes[i] != nullptr)
			return mNodes[i]->Erase(colliderIndex);
	}

	return false;
}

bool QuadTree::Erase(int colliderIndex, Bounds bounds)
{
	int index = GetChildNodeIndex(bounds);
	if (index != -1 && mNodes[0] != nullptr)
	{
		if (mNodes[index]->Erase(colliderIndex, bounds))
			return true;
	}

	for (int i = 0; i < mObjects.size(); i++)
	{
		if (mObjects[i].colliderIndex == colliderIndex)
		{
			mObjects.erase(mObjects.begin() + i);
			return true;
		}
	}

	return false;
}

std::vector<int> QuadTree::Retrieve(std::vector<int> &objects, Bounds bounds)
{
	int index = GetChildNodeIndex(bounds);
	if (index != -1 && mNodes[0] != nullptr)
	{
		mNodes[index]->Retrieve(objects, bounds);
	}

	for (int i = 0; i < mObjects.size(); i++)
	{
		if (mObjects[i].colliderIndex != -1)
		{
			objects.push_back(mObjects[i].colliderIndex);
		}
	}

	return objects;
}


