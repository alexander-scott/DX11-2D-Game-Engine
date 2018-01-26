#include "ComponentFactory.h"


TransformComponent * ComponentFactory::MakeTransform(Vec2 position, float rotation, float scale)
{
	TransformComponent * transform = new TransformComponent(position, rotation, scale);

	return transform;
}

SpriteRendererComponent * ComponentFactory::MakeSpriteRenderer(std::string fileName, int renderLayer, TransformComponent* transform, float width, float height, Vec2 offset)
{
	SpriteRendererComponent * spriteRenderer = new SpriteRendererComponent(renderLayer);
	spriteRenderer->SetFilename(fileName);
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	spriteRenderer->SetTransform(transform);
	spriteRenderer->SetOffset(offset);
	spriteRenderer->SetWidthHeight(width, height);

	return spriteRenderer;
}

SpriteAnimatorComponent * ComponentFactory::MakeSpriteAnimator(std::string fileName, int renderLayer, TransformComponent * transform, float width, float height, std::vector<AnimationDesc> animDescs, int currentAnim)
{
	SpriteAnimatorComponent * spriteAnimator = new SpriteAnimatorComponent(renderLayer);
	spriteAnimator->SetFilename(fileName);
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	spriteAnimator->SetTransform(transform);
	spriteAnimator->SetAnimations(currentAnim, animDescs);
	spriteAnimator->SetWidthHeight(width, height);

	return spriteAnimator;
}

RigidBodyComponent * ComponentFactory::MakeRigidbody(float staticF, float dynamicF, float rest, bool isStatic, bool lockRotation)
{
	RigidBodyComponent * rigidBody = new RigidBodyComponent(staticF, dynamicF, rest);
	if (isStatic)
		rigidBody->SetStatic();
	if (lockRotation)
		rigidBody->LockRotation();

	return rigidBody;
}

TextRendererComponent * ComponentFactory::MakeTextRenderer(std::string text, XMVECTORF32 colour, TransformComponent * transform)
{
	TextRendererComponent * textRenderer = new TextRendererComponent();
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	textRenderer->SetTransform(transform);
	textRenderer->SetText(text);
	textRenderer->SetTextColour(colour);

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
	circleCollider->SetRadius(radius * transform->GetWorldScale());
	circleCollider->ComputeMass(2);

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
	polygonCollider->ComputeMass(0.3f);

	delete verticies;

	return polygonCollider;
}

BoxColliderComponent * ComponentFactory::MakeBoxCollider(float width, float height, TransformComponent * transform, RigidBodyComponent * rigidBody)
{
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	if (rigidBody == nullptr)
	{
		throw std::exception("This object requires a rigidbody component.");
	}

	BoxColliderComponent * boxCollider = new BoxColliderComponent(transform, rigidBody);
	boxCollider->SetBox((width/2) * transform->GetWorldScale(), (height/2) * transform->GetWorldScale());
	boxCollider->ComputeMass(0.3f);

	return boxCollider;
}

GUITextComponent * ComponentFactory::MakeGUIText(std::string text, int renderLayer, float r, float g, float b, TransformComponent* transform, Vec2 offset)
{
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}

	GUITextComponent* guiText = new GUITextComponent(renderLayer);
	guiText->SetText(text);
	guiText->SetTransform(transform);
	guiText->SetTextColour(r, g, b);
	guiText->SetOffset(offset);

	return guiText;
}

GUISpriteRendererComponent * ComponentFactory::MakeGUISpriteRenderer(std::string fileName, int renderLayer, TransformComponent * transform, float width, float height, Vec2 offset)
{
	GUISpriteRendererComponent * spriteRenderer = new GUISpriteRendererComponent(renderLayer);
	spriteRenderer->SetFilename(fileName);
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	spriteRenderer->SetTransform(transform);
	spriteRenderer->SetOffset(offset);
	spriteRenderer->SetWidthHeight(width, height);

	return spriteRenderer;
}

GUIButtonComponent * ComponentFactory::MakeGUIButton(TransformComponent * transform, float width, float height)
{
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	GUIButtonComponent * guiButton = new GUIButtonComponent(transform, width, height);
	return guiButton;
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

TiledBGRenderer * ComponentFactory::MakeTiledBGRenderer(std::string spriteName, int renderLayer, float spriteWidth, float spriteHeight, float moveRate, TiledBGDirection direction, TransformComponent * trans, TransformComponent * focusTrans)
{
	if (trans == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	if (focusTrans == nullptr)
	{
		throw std::exception("This object requires a focus transform component");
	}

	TiledBGRenderer * bgRenderer = new TiledBGRenderer(renderLayer);
	bgRenderer->SetTransform(trans);
	bgRenderer->SetFocusTrans(focusTrans);
	bgRenderer->SetScrollRate(moveRate);
	bgRenderer->SetDirection(direction);
	bgRenderer->SetSprite(spriteName, spriteWidth, spriteHeight);

	return bgRenderer;
}

TriggerBoxComponent * ComponentFactory::MakeTriggerBox(std::string triggerTag)
{
	TriggerBoxComponent* triggerBox = new TriggerBoxComponent(triggerTag);
	return triggerBox;
}
