#include "AddForceMessage.h"



AddForceMessage::AddForceMessage(std::string name) : _name(name)
{
	_type = MessageType::AddForce;
}

AddForceMessage::~AddForceMessage()
{
}
