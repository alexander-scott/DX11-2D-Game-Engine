#pragma once

#include <string>

class IObject
{
public:
	IObject(std::string tag, int id) : mTag(tag), mID(id) { }

	std::string GetTag() { return mTag; }
	int GetID() { return mID; }

protected:
	std::string		mTag;
	int				mID;
};