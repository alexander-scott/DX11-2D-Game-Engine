#pragma once

#include <map>
#include <vector>

#include "IEMath.h"

#pragma region Values

static constexpr int SCREEN_WIDTH = 800;
static constexpr int SCREEN_HEIGHT = 600;

#pragma endregion

#pragma region Enums

enum AnimationType
{
	WalkingUp,
	WalkingLeft,
	WalkingDown,
	WalkingRight,
	StandingUp,
	StandingLeft,
	StandingDown,
	StandingRight,
	Count
};

enum MessageType
{
	UpdateAnimationSequence,
	AddForce
};

enum ColliderType 
{
	eCircle,
	ePolygon,
	eColliderTypeCount
};

enum CollisionType 
{
	eCircletoCircle,
	eCircleToPolygon,
	ePolygonToCircle,
	ePolygonToPolygon
};

#pragma endregion

#pragma region Maps

static std::map<std::string, std::string> SpriteFilePaths = 
{
	{ "MageWalk",		"Images\\mage_walk.dds" },
	{ "Pipe",			"Images\\warp_pipe_edited.dds" },
};

#pragma endregion

#pragma region Structs

struct AnimationDesc 
{
	int StartingIndex; // Loop start pos
	int EndingIndex; // Loop end pos
	int X;
	int Y;
	int Width;
	int Height;
	int FrameCount;
	float HoldTime;

	AnimationDesc(int startingIndex, int endingIndex, int x, int y, int width, int height, int frameCount, float holdTime) 
		: StartingIndex(startingIndex), EndingIndex(endingIndex), X(x), Y(y), Width(width), Height(height), FrameCount(frameCount), HoldTime(holdTime)
	{

	}
};

struct RigidBodyData 
{
	Vec2 velocity;

	float angularVelocity;
	float torque;
	float orient; // radians

	Vec2 force;

	// Set by rigidbody
	float intertia;  // moment of inertia
	float inverseInertia; // inverse inertia
	float mass;  // mass
	float inverseMass; // inverse masee

	float staticFriction;
	float dynamicFriction;
	float restitution;

	RigidBodyData(Vec2 velocity, float angularVelocity, float torque, float orient, Vec2 force, float staticFriction, float dynamicFrication, float restituation)
		: velocity(velocity), angularVelocity(angularVelocity), torque(torque), orient(orient), force(force), 
		staticFriction(staticFriction), dynamicFriction(dynamicFrication), restitution(restituation)
	{

	}
};

struct LevelData 
{
public:
	int levelWidth;
	int levelHeight;

	float playerXPos;
	float playerYPos;
};

#pragma endregion
