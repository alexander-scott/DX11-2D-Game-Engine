#include "GameComponentFactory.h"


PlayerComponent * ComponentFactory::MakePlayerComponent(TransformComponent* trans, SpriteAnimatorComponent * anim, 
	RigidBodyComponent * rb, DamageableComponent* dmg, ProjectileManagerComponent* proj, TransformComponent* cameraTrans)
{
	if (trans == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	if (anim == nullptr)
	{
		throw std::exception("This object requires a animator component.");
	}
	if (rb == nullptr)
	{
		throw std::exception("This object requires a rigidbody component.");
	}
	if (dmg == nullptr)
	{
		throw std::exception("This object requires a damageable component.");
	}
	if (proj == nullptr)
	{
		throw std::exception("This object requires a projectile manager component.");
	}
	if (cameraTrans == nullptr)
	{
		throw std::exception("This object requires a camera transform.");
	}

	PlayerComponent* playerComponent = new PlayerComponent(trans, anim, rb, dmg, proj, cameraTrans);

	return playerComponent;
}

DamageableComponent * ComponentFactory::MakeDamageableComponent(float startHealth, std::string hitNoise)
{
	DamageableComponent* damageComponent = new DamageableComponent(startHealth, hitNoise);
	return damageComponent;
}

ProjectileComponent * ComponentFactory::MakeProjectileComponent(std::string affectedTag, float lifeSpan, float dmg)
{
	ProjectileComponent* projectileComponent = new ProjectileComponent(affectedTag, lifeSpan, dmg);
	return projectileComponent;
}

ProjectileManagerComponent * ComponentFactory::MakeProjectileManagerComponent(std::vector<shared_ptr<GameObject>> projectiles)
{
	ProjectileManagerComponent* projComponent = new ProjectileManagerComponent;
	projComponent->AddCreatedGameObjects(projectiles);
	return projComponent;
}

AIAgentComponent * ComponentFactory::MakeAIAgentComponent(TransformComponent * trans, SpriteAnimatorComponent * anim, RigidBodyComponent * rb, DamageableComponent * dmg, 
	ProjectileManagerComponent * proj, TransformComponent * cameraTransform, float patrolTime, AIAgentPatrolDirection patrolStartDir, float idleTime, TransformComponent* targetTransform, float viewRange, float shotInterval)
{
	if (trans == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	if (anim == nullptr)
	{
		throw std::exception("This object requires a animator component.");
	}
	if (rb == nullptr)
	{
		throw std::exception("This object requires a rigidbody component.");
	}
	if (dmg == nullptr)
	{
		throw std::exception("This object requires a damageable component.");
	}
	if (proj == nullptr)
	{
		throw std::exception("This object requires a projectile manager component.");
	}
	if (cameraTransform == nullptr)
	{
		throw std::exception("This object requires a camera transform.");
	}

	AIAgentComponent* agentComponent = new AIAgentComponent(trans, anim, rb, dmg, cameraTransform);
	agentComponent->SetupPatrolling(patrolTime, patrolStartDir, idleTime);
	agentComponent->SetupShooting(proj, targetTransform, viewRange, shotInterval);

	return agentComponent;
}

GUITextValueComponent * ComponentFactory::MakeGUITextValueComponent(std::string valueName, std::string text, float r, float g, float b, TransformComponent* transform, Vec2 offset)
{
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}

	GUITextValueComponent* guiText = new GUITextValueComponent(valueName);
	guiText->SetText(text);
	guiText->SetTransform(transform);
	guiText->SetTextColour(r, g, b);
	guiText->SetOffset(offset);

	return guiText;
}

GameCameraComponent * ComponentFactory::MakeGameCameraComponent(TransformComponent* trans, TransformComponent* focusTrans, 
	float focusWidth, float focusHeight, float leftBound, float rightBound, float topBound, float bottomBound)
{
	if (focusTrans == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}

	GameCameraComponent* camera = new GameCameraComponent(trans, focusTrans, focusWidth, focusHeight);
	camera->SetLevelBounds(leftBound, rightBound, bottomBound, topBound);
	return camera;
}
