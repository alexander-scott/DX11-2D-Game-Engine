#pragma once

#include "IMessage.h"
#include "IEMath.h"

class AddForceMessage : public IMessage
{
public:
	AddForceMessage()
	{
		_type = MessageType::AddForce;
	}

	void SetForce(Vec2 force) { _force = force; }
	Vec2 GetForce() { return _force; }

private:
	Vec2				_force;
};

