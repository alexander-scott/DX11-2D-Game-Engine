#include "ProjectileComponent.h"

ProjectileComponent::ProjectileComponent(std::string affectedTag, float lifeSpan, float dmg)
{
	mAffectedTag = affectedTag;
	mLifeLeft = lifeSpan;
	mStartingLife = lifeSpan;
	mDamage = dmg;

	mIsDead = false;
}

ProjectileComponent::~ProjectileComponent()
{
}

void ProjectileComponent::RecieveMessage(IMessage & msg)
{
	switch (msg.GetType())
	{
		case MessageType::eCollision:
		{
			CollisionMessage& colMsg = static_cast<CollisionMessage &> (msg);
			if (colMsg.CollidedObject->GetTag() == mAffectedTag)
			{
				RecieveDamageMessage recieveDmg(mDamage);
				colMsg.CollidedObject->SendMessageToComponents(recieveDmg);
				mIsDead = true;
			}

			break;
		}
	}
}

void ProjectileComponent::Update(float deltaTime)
{
	mLifeLeft -= deltaTime;
	if (mLifeLeft < 0)
	{
		mIsDead = true;
	}
}

void ProjectileComponent::Reset()
{
	mLifeLeft = mStartingLife;
	mIsDead = false;
}

void ProjectileComponent::Reset(float lifeSpan)
{
	mStartingLife = lifeSpan;
	mLifeLeft = lifeSpan;
	mIsDead = false;
}

void ProjectileComponent::Reset(std::string affectedTag, float damage)
{
	mLifeLeft = mStartingLife;
	mIsDead = false;

	mAffectedTag = affectedTag;
	mDamage = damage;
}
