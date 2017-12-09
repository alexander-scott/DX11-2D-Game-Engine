#include "WorldTile.h"

WorldTile::WorldTile(std::string fileName, Vec2 pos)
{
	TransformComponent* pipeTransform = ComponentFactory::MakeTransform(pos, 0, 0.3);
	SpriteRendererComponent* pipeSprite = ComponentFactory::MakeSpriteRenderer(fileName, pipeTransform);
	RigidBodyComponent* pipeRigidbody = ComponentFactory::MakeRigidbody(true);

	BoxColliderComponent * pipeCollider = ComponentFactory::MakeBoxCollider(25, 25, pipeTransform, pipeRigidbody);

	AddComponent(pipeTransform);
	AddComponent(pipeSprite);
	AddComponent(pipeRigidbody);
	AddComponent(pipeCollider);

	pipeRigidbody->SetStatic();
}
