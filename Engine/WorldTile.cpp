#include "WorldTile.h"

WorldTile::WorldTile(std::string fileName, Vec2 pos)
{
	TransformComponent* pipeTransform = ComponentFactory::MakeTransform(pos, 0, 0.3);
	SpriteRendererComponent* pipeSprite = ComponentFactory::MakeSpriteRenderer(fileName, pipeTransform);
	RigidBodyComponent* pipeRigidbody = ComponentFactory::MakeRigidbody(true);

	// 0,0 is TOP LEFT CORNER
	Vec2 *vertices = new Vec2[4];
	vertices[0].Set(10, 10);
	vertices[1].Set(-20, 10);
	vertices[2].Set(10, -30);
	vertices[3].Set(-20, -30);

	PolygonColliderComponent * pipeCollider = ComponentFactory::MakePolygonCollider(vertices, 4, pipeTransform, pipeRigidbody);

	AddComponent(pipeTransform);
	AddComponent(pipeSprite);
	AddComponent(pipeRigidbody);
	AddComponent(pipeCollider);
}
