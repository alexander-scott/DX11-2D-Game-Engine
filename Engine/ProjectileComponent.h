#pragma once

#include "IComponent.h"
#include "IMessageable.h"
#include "IUpdateable.h"

#include "CollisionMessage.h"
#include "RecieveDamageMessage.h"

class ProjectileComponent : public IComponent, public IMessageable, public IUpdateable
{
public:
	ProjectileComponent(std::string affectedTag, float lifeSpan, float dmg);
	~ProjectileComponent();

	virtual void RecieveMessage(IMessage &msg) override;
	virtual void Update(float deltaTime) override;

	bool IsDead() { return mIsDead; }
	void Reset();
	void Reset(float lifeSpan);
	void Reset(std::string affectedTag, float damage);

private:
	std::string		mAffectedTag;
	float			mDamage;

	float			mStartingLife;
	float			mLifeLeft;
	bool			mIsDead;
};

