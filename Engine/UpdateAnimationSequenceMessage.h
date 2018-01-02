#pragma once

#include "IMessage.h"

class UpdateAnimationSequenceMessage : public IMessage
{
public:
	UpdateAnimationSequenceMessage()
	{
		mMessageType = MessageType::eUpdateAnimationSequence;
	}

	void SetSequence(int seq) { mSequence = seq; }
	int GetSequence() { return mSequence; }

private:
	int				mSequence;
};