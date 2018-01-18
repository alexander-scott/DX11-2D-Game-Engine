#pragma once

#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include "SpriteAnimatorComponent.h"
#include "RigidBodyComponent.h"
#include "TextRendererComponent.h"
#include "ColliderComponent.h"
#include "CircleColliderComponent.h"
#include "PolygonColliderComponent.h"
#include "BoxColliderComponent.h"
#include "ColliderRendererComponent.h"
#include "TiledBGRenderer.h"
#include "GUITextComponent.h"
#include "GUISpriteRendererComponent.h"
#include "GUIButtonComponent.h"
#include "TriggerBoxComponent.h"

namespace ComponentFactory
{
	TransformComponent * MakeTransform(Vec2 position, float rotation, float scale);
	
	RigidBodyComponent * MakeRigidbody(float staticF, float dynamicF, float rest, bool isStatic, bool lockRotation);

	TextRendererComponent * MakeTextRenderer(std::string text, XMVECTORF32 colour, TransformComponent* transform);
	SpriteRendererComponent * MakeSpriteRenderer(std::string fileName, int renderLayer, TransformComponent* transform, float width, float height, Vec2 offset);
	SpriteAnimatorComponent * MakeSpriteAnimator(std::string fileName, int renderLayer, TransformComponent* transform, float width, float height, std::vector<AnimationDesc> animDescs, int currentAnim);
	ColliderRendererComponent * MakeColliderRenderer(TransformComponent* trans, ColliderComponent* collider);
	TiledBGRenderer * MakeTiledBGRenderer(std::string spriteName, int renderLayer, float spriteWidth, float spriteHeight, float moveRate, TiledBGDirection direction, TransformComponent* trans, TransformComponent* focusTrans);

	CircleColliderComponent * MakeCircleCollider(float radius, TransformComponent* transform, RigidBodyComponent* rigidbody);
	PolygonColliderComponent * MakePolygonCollider(Vec2* verticies, int vertexCount, TransformComponent* transform, RigidBodyComponent* rigidbody);
	BoxColliderComponent * MakeBoxCollider(float width, float height, TransformComponent* transform, RigidBodyComponent* rigidBody);

	TriggerBoxComponent * MakeTriggerBox(std::string triggerTag);

	GUITextComponent * MakeGUIText(std::string text, float r, float g, float b, TransformComponent* transform, Vec2 offset);
	GUISpriteRendererComponent * MakeGUISpriteRenderer(std::string fileName, int renderLayer, TransformComponent* transform, float width, float height, Vec2 offset);
	GUIButtonComponent * MakeGUIButton(TransformComponent* transform, float width, float height);
};