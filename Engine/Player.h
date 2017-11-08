#pragma once

#include "GameObject.h"
#include "ComponentFactory.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	virtual void Update(float deltaTime) override;

private:
	RigidBodyComponent* playerRigidBody;
	SpriteAnimatorComponent* playerAnimator;
};

