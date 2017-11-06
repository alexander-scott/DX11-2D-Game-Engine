#pragma once

#include "Consts.h"

class IMessage
{
protected:
	MessageType _type;

public:
	virtual MessageType GetType() const { return _type; }
};