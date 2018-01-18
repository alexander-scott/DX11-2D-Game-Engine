#pragma once

#include "IComponent.h"
#include "IMessageable.h"
#include "IUpdateable.h"

#include "CollisionMessage.h"

class TriggerBoxComponent :	public IComponent, public IMessageable
{
public:
	TriggerBoxComponent(std::string triggerTag);
	~TriggerBoxComponent();

	virtual void RecieveMessage(IMessage &msg) override;

	bool IsTriggered() { return mIsTriggered; }
	bool& GetTriggeredReference() { return mIsTriggered; }

private:
	bool				mIsTriggered;
	std::string			mTriggerTag;
};