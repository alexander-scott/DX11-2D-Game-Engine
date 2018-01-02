#pragma once

#include "IMessage.h"

class RecieveDamageMessage : public IMessage
{
public:
	RecieveDamageMessage(float damage)
	{
		mMessageType = MessageType::eRecieveDamage;
		Damage = damage;
	}

	float Damage;
};