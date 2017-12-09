#include "WorldTile.h"

WorldTile::WorldTile(std::string fileName, Vec2 pos)
{
	TransformComponent* pipeTransform = ComponentFactory::MakeTransform(pos, 0, 1);
	SpriteRendererComponent* pipeSprite = ComponentFactory::MakeSpriteRenderer(fileName, pipeTransform, 45, 45, Vec2(0,0));
	RigidBodyComponent* pipeRigidbody = ComponentFactory::MakeRigidbody(1,1,1);

	BoxColliderComponent * pipeCollider = ComponentFactory::MakeBoxCollider(23, 30, pipeTransform, pipeRigidbody);

	AddComponent(pipeTransform);
	AddComponent(pipeSprite);
	AddComponent(pipeRigidbody);
	AddComponent(pipeCollider);

	pipeRigidbody->SetStatic();
}
