#pragma once

#include "IMessage.h"

#include "GameObject.h"

class CollisionMessage : public IMessage
{
public:
	CollisionMessage(GameObject* collidedObj)
	{
		_type = MessageType::Collision;
		collidedObject = collidedObj;
	}

	
	GameObject* collidedObject;
};