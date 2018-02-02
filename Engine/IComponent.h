#pragma once

#include <string>
#include "IObject.h"

using namespace std;

class IComponent
{
public:
	virtual string GetType() { return mType; }

	void SetGameObject(IObject* obj) { mGameObject = obj; }
	IObject* GetGameObject() { return mGameObject; }

	void SetActive(bool active) { mActive = active; }
	bool GetActive() { return mActive; }

protected:
	string			mType;
	bool			mActive = true;
	IObject*		mGameObject;
};