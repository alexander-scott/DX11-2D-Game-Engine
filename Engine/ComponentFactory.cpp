#include "ComponentFactory.h"


TransformComponent * ComponentFactory::MakeTransform(Vec2 position, float rotation, float scale)
{
	TransformComponent * transform = new TransformComponent();
	transform->SetPosition(position);
	transform->SetRotation(rotation);
	transform->SetScale(scale);

	return transform;
}

SpriteRendererComponent * ComponentFactory::MakeSpriteRenderer(SpriteName fileName, TransformComponent* transform)
{
	SpriteRendererComponent * spriteRenderer = new SpriteRendererComponent();
	spriteRenderer->SetFilename(fileName);
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	spriteRenderer->SetTransform(transform);

	return spriteRenderer;
}

SpriteAnimatorComponent * ComponentFactory::MakeSpriteAnimator(SpriteName fileName, TransformComponent * transform, std::vector<AnimationDesc> animDescs, int currentAnim)
{
	SpriteAnimatorComponent * spriteAnimator = new SpriteAnimatorComponent();
	spriteAnimator->SetFilename(fileName);
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	spriteAnimator->SetTransform(transform);
	spriteAnimator->SetAnimations(currentAnim, animDescs);

	return spriteAnimator;
}

RigidBodyComponent * ComponentFactory::MakeRigidbody(bool setStatic)
{
	RigidBodyComponent * rigidBody = new RigidBodyComponent();
	if (setStatic)
	{
		rigidBody->SetStatic();
	}

	return rigidBody;
}

TextRendererComponent * ComponentFactory::MakeTextRenderer(std::string text, TransformComponent * transform)
{
	TextRendererComponent * textRenderer = new TextRendererComponent();
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	textRenderer->SetTransform(transform);
	textRenderer->SetText(text);

	return textRenderer;
}

CircleColliderComponent * ComponentFactory::MakeCircleCollider(float radius, TransformComponent * transform, RigidBodyComponent * rigidbody)
{
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	if (rigidbody == nullptr)
	{
		throw std::exception("This object requires a rigidbody component.");
	}

	CircleColliderComponent * circleCollider = new CircleColliderComponent(transform, rigidbody);
	circleCollider->SetRadius(radius);

	return circleCollider;
}

PolygonColliderComponent * ComponentFactory::MakePolygonCollider(Vec2 * verticies, int vertexCount, TransformComponent * transform, RigidBodyComponent * rigidbody)
{
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	if (rigidbody == nullptr)
	{
		throw std::exception("This object requires a rigidbody component.");
	}

	PolygonColliderComponent * polygonCollider = new PolygonColliderComponent(transform, rigidbody);
	polygonCollider->SetVerticies(verticies, vertexCount);
	polygonCollider->SetOrient(0);

	delete verticies;

	return polygonCollider;
}

ColliderRendererComponent * ComponentFactory::MakeColliderRenderer(TransformComponent* trans, ColliderComponent* collider)
{
	if (trans == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	if (collider == nullptr)
	{
		throw std::exception("This object requires a collider component");
	}

	ColliderRendererComponent * colliderRenderer = new ColliderRendererComponent();
	colliderRenderer->SetCollider(collider);
	colliderRenderer->SetTransform(trans);

	return colliderRenderer;
}
