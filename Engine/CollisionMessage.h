#pragma once

#include "IMessage.h"

#include "GameObject.h"

class CollisionMessage : public IMessage
{
public:
	CollisionMessage(GameObject* collidedObj)
	{
		mMessageType = MessageType::eCollision;
		CollidedObject = collidedObj;
	}
	
	GameObject* CollidedObject;
};