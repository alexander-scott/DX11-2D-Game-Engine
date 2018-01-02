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

	TransformComponent*			mPlayerTransform;
	SpriteAnimatorComponent*	mPlayerAnimator;
	RigidBodyComponent*			mPlayerRigidBody;
	DamageableComponent*		mPlayerDamageable;

	ProjectileManagerComponent*	mPlayerProjectiles;
	TransformComponent*			mCameraTransform;

	bool						mIsGrounded;
	bool						mCanJump;
	bool						mIsShooting;
};

