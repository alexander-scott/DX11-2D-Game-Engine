#pragma once

#include "IComponent.h"
#include "IUpdateable.h"
#include "IMessageable.h"

#include "RigidBodyComponent.h"
#include "SpriteAnimatorComponent.h"

class PlayerComponent : public IComponent, public IUpdateable, public IMessageable
{
public:
	PlayerComponent(TransformComponent* trans, SpriteAnimatorComponent* anim, RigidBodyComponent* rb);
	~PlayerComponent();

	virtual void Update(float deltaTime) override;
	virtual void RecieveMessage(IMessage & message) override;

private:
	void UpdateAnimation();
	void CheckInput();

	TransformComponent*			_playerTransform;
	SpriteAnimatorComponent*	_playerAnimator;
	RigidBodyComponent*			_playerRigidBody;

	bool						_grounded;
};

