#pragma once

#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include "SpriteAnimatorComponent.h"
#include "RigidBodyComponent.h"
#include "TextRendererComponent.h"
#include "ColliderComponent.h"
#include "CircleColliderComponent.h"
#include "PolygonColliderComponent.h"
#include "ColliderRendererComponent.h"
#include "TiledBGRenderer.h"

namespace ComponentFactory
{
	TransformComponent * MakeTransform(Vec2 position, float rotation, float scale);
	
	RigidBodyComponent * MakeRigidbody(bool setStatic);

	TextRendererComponent * MakeTextRenderer(std::string text, TransformComponent* transform);
	SpriteRendererComponent * MakeSpriteRenderer(std::string fileName, TransformComponent* transform);
	SpriteAnimatorComponent * MakeSpriteAnimator(std::string fileName, TransformComponent* transform, std::vector<AnimationDesc> animDescs, int currentAnim);
	ColliderRendererComponent * MakeColliderRenderer(TransformComponent* trans, ColliderComponent* collider);
	TiledBGRenderer * MakeTiledBGRenderer(std::string spriteName, float spriteWidth, float spriteHeight, TransformComponent* trans, TransformComponent* focusTrans);

	CircleColliderComponent * MakeCircleCollider(float radius, TransformComponent* transform, RigidBodyComponent* rigidbody);
	PolygonColliderComponent * MakePolygonCollider(Vec2* verticies, int vertexCount, TransformComponent* transform, RigidBodyComponent* rigidbody);
};