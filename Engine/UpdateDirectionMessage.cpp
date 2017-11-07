#include "UpdateDirectionMessage.h"



UpdateDirectionMessage::UpdateDirectionMessage(std::string name) : _name(name)
{
	_type = MessageType::UpdateDirection;
}


UpdateDirectionMessage::~UpdateDirectionMessage()
{
}
