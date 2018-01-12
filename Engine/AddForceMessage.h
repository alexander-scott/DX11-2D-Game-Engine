#pragma once

#include "IMessage.h"

struct Vec2;

class AddForceMessage : public IMessage
{
public:
	AddForceMessage(Vec2 force)
	{
		mMessageType = MessageType::eAddForce;
		Force = force;
	}

	Vec2				Force;
};

