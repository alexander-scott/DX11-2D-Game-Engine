#pragma once

#include "IMessage.h"
#include "IEMath.h"

class UpdateDirectionMessage : public IMessage
{
public:
	UpdateDirectionMessage(std::string name);
	~UpdateDirectionMessage();

	void SetDir(Vec2 dir) { _dir = dir; }
	Vec2 GetDir() { return _dir; }

private:
	std::string _name;
	Vec2		_dir;
};

