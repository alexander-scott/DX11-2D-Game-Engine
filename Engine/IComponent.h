#pragma once

#include <string>

using namespace std;

class IComponent
{
protected:
	string			_type;

public:
	virtual string GetType() { return _type; }
};