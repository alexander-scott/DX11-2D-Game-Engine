#include "ComponentFactory.h"


TransformComponent * ComponentFactory::MakeTransform(Vec2 position, float rotation, float scale)
{
	TransformComponent * transform = new TransformComponent();
	transform->SetPosition(position);
	transform->SetRotation(rotation);
	transform->SetScale(scale);

	return transform;
}

SpriteRendererComponent * ComponentFactory::MakeSpriteRenderer(std::string fileName, TransformComponent* transform)
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

SpriteAnimatorComponent * ComponentFactory::MakeSpriteAnimator(std::string fileName, TransformComponent * transform, std::vector<AnimationDesc> animDescs, int currentAnim)
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

RigidBodyComponent * ComponentFactory::MakeRigidbody(TransformComponent* transform)
{
	RigidBodyComponent * rigidBody = new RigidBodyComponent();
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	rigidBody->SetTransform(transform);

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
