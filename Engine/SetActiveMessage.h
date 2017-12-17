#pragma once

#include "IMessage.h"

class SetActiveMessage : public IMessage 
{
public:
	SetActiveMessage(bool active) 
	{
		_type = MessageType::eSetActive;
		Active = active;
	}

	bool Active;
};
