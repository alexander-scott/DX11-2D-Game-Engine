#include "ComponentFactory.h"


TransformComponent * ComponentFactory::MakeTransform(Vec2 position)
{
	TransformComponent * transform = new TransformComponent();
	transform->SetPosition(position);

	return transform;
}

SpriteRendererComponent * ComponentFactory::MakeSpriteRenderer(std::string fileName, TransformComponent* transform)
{
	SpriteRendererComponent * spriteRenderer = new SpriteRendererComponent();
	spriteRenderer->SetFilename(fileName);
	spriteRenderer->SetTransform(transform);

	return spriteRenderer;
}

SpriteAnimatorComponent * ComponentFactory::MakeSpriteAnimator(std::string fileName, TransformComponent * transform, std::vector<AnimationDesc> animDescs)
{
	SpriteAnimatorComponent * spriteAnimator = new SpriteAnimatorComponent(animDescs);
	spriteAnimator->SetFilename(fileName);
	spriteAnimator->SetTransform(transform);

	return spriteAnimator;
}
