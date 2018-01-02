#pragma once

#include "Consts.h"

class IMessage
{
public:
	virtual MessageType GetType() const { return mMessageType; }

protected:
	MessageType mMessageType;
};