#pragma once

#include "IMessage.h"

#include "GameObject.h"

class CollisionMessage : public IMessage
{
public:
	CollisionMessage(shared_ptr<GameObject> collidedObj)
	{
		mMessageType = MessageType::eCollision;
		CollidedObject = collidedObj;
	}
	
	shared_ptr<GameObject> CollidedObject;
};