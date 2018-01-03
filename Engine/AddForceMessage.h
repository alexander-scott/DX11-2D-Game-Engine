#pragma once

#include "IMessage.h"
#include "Consts.h"

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

