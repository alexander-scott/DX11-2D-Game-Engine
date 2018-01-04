#include "TriggerBoxComponent.h"



TriggerBoxComponent::TriggerBoxComponent(std::string triggerTag) : mTriggerTag(triggerTag)
{
	mIsTriggered = false;
}


TriggerBoxComponent::~TriggerBoxComponent()
{
}

void TriggerBoxComponent::RecieveMessage(IMessage & msg)
{
	switch (msg.GetType())
	{
		case MessageType::eCollision:
		{
			CollisionMessage& colMsg = static_cast<CollisionMessage &> (msg);
			if (colMsg.CollidedObject->GetTag() == mTriggerTag)
			{
				mIsTriggered = true;
			}

			break;
		}
	}
}