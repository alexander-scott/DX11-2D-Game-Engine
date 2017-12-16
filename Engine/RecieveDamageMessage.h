#pragma once

#include "IMessage.h"

class RecieveDamageMessage : public IMessage
{
public:
	RecieveDamageMessage(float damage)
	{
		_type = MessageType::eRecieveDamage;
		_damage = damage;
	}

	float _damage;
};