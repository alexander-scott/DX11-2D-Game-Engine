#pragma once

#include <string>

using namespace std;

class IComponent
{
protected:
	string			_type;
	bool			_active = true;

public:
	virtual string GetType() { return _type; }

	void SetActive(bool active) { _active = active; }
	bool GetActive() { return _active; }
};