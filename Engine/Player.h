#pragma once

#include "Keyboard.h"
#include "GameObject.h"
#include "ComponentFactory.h"

#include "AddForceMessage.h"
#include "UpdateAnimationSequenceMessage.h"

class Player : public GameObject
{
public:
	Player(std::string tag, float xPos, float yPos);
	~Player();

	virtual void Update(float deltaTime) override;

private:
	void UpdateAnimation();
	void CheckInput();

	RigidBodyComponent* playerRigidBody;
};

