#pragma once

#include "IMessage.h"

class UpdateAnimationSequenceMessage : public IMessage
{
public:
	UpdateAnimationSequenceMessage()
	{
		_type = MessageType::eUpdateAnimationSequence;
	}

	void SetSequence(int seq) { _sequence = seq; }
	int GetSequence() { return _sequence; }

private:
	int				_sequence;
};