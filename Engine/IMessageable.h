#pragma once

#include "IMessage.h"

class IMessageable
{
public:
	virtual void RecieveMessage(IMessage & message) = 0;
};