#pragma once

#include <string>

using namespace std;

class IComponent
{
public:
	virtual string GetType() { return mType; }

	void SetActive(bool active) { mActive = active; }
	bool GetActive() { return mActive; }

protected:
	string			mType;
	bool			mActive = true;
};