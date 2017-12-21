#pragma once

#include "IComponent.h"
#include "IUpdateable.h"
#include "IMessageable.h"

#include "RigidBodyComponent.h"
#include "SpriteAnimatorComponent.h"
#include "DamageableComponent.h"

#include "ProjectileManagerComponent.h"
#include "Audio.h"

class PlayerComponent : public IComponent, public IUpdateable, public IMessageable
{
public:
	PlayerComponent(TransformComponent* trans, SpriteAnimatorComponent* anim, 
		RigidBodyComponent* rb, DamageableComponent* dmg, ProjectileManagerComponent* projectileMan, TransformComponent* cameraTransform);
	~PlayerComponent();

	virtual void Update(float deltaTime) override;
	virtual void RecieveMessage(IMessage & message) override;

private:
	void UpdateAnimation();
	void CheckInput();

	void ShootProjectile();

	TransformComponent*			_playerTransform;
	SpriteAnimatorComponent*	_playerAnimator;
	RigidBodyComponent*			_playerRigidBody;
	DamageableComponent*		_playerDamageable;

	ProjectileManagerComponent*	_playerProjectiles;
	TransformComponent*			_cameraTransform;

	bool						_grounded;
	bool						_canJump;
	bool						_isShooting;
};

