#pragma once

#include "IComponent.h"
#include "IUpdateable.h"

#include "RigidBodyComponent.h"
#include "SpriteAnimatorComponent.h"

class PlayerComponent : public IComponent, public IUpdateable
{
public:
	PlayerComponent(SpriteAnimatorComponent* anim, RigidBodyComponent* rb);
	~PlayerComponent();

	virtual void Update(float deltaTime) override;

private:
	void UpdateAnimation();
	void CheckInput();

	SpriteAnimatorComponent*	_playerAnimator;
	RigidBodyComponent*			_playerRigidBody;
};

