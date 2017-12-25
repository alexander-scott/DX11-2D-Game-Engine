#pragma once

#include <map>
#include <vector>

#include "IEMath.h"

#pragma region GamePlay Vals

// PLAYER //
static float PLAYER_PROJECTILE_DAMAGE = 20; // Default 20
static float PLAYER_PROJECTILE_SPEED = 50; // Default 50
static float PLAYER_LATERAL_MAX_SPEED = 500; // Default is 500

// AI //
static float AI_PROJECTILE_DAMAGE = 20; // Default 20
static float AI_PROJECTILE_SPEED = 50; // Default 50
static float AI_LATERAL_MAX_SPEED = 300; // Default is 300

#pragma endregion

#pragma region Application Values

static constexpr int SCREEN_WIDTH = 800;
static constexpr int SCREEN_HEIGHT = 600;

static constexpr int TILE_WIDTH = 45;
static constexpr int TILE_HEIGHT = 45;

static constexpr int X_ORIGIN = 0;
static constexpr int Y_ORIGIN = 0;

static constexpr int MAX_QUADTREE_OBJECTS = 10;
static constexpr int MAX_QUADTREE_LEVELS = 5;

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
	eUpdateAnimationSequence,
	eAddForce,
	eCollision,
	eRecieveDamage,
	eSetActive
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

enum TiledBGDirection
{
	eHorizontal,
	eVertical,
	eHoriztonalAndVertical
};

enum AIAgentState 
{
	ePatrolling,
	eShooting
};

enum AIAgentPatrolDirection
{
	ePatrollingLeft,
	ePatrollingRight
};

#pragma endregion

#pragma region Maps

static std::map<std::string, std::string> SpriteFilePaths = 
{
	{ "MageWalk",		"Images\\mage_walk.dds" },
	{ "Ball",			"Images\\ColourBall.dds" },
	{ "Pipe",			"Images\\NewPipe.dds" },
	{ "BG_Sky",			"Images\\Backgrounds\\Sky_back_layer.dds" },
	{ "BG_Vegetation",	"Images\\Backgrounds\\Vegetation_layer.dds" },
	{ "BG_Ground",		"Images\\Backgrounds\\Ground_(front_layer).dds" },
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

	Vec2 force;

	Mat2 orientationMatrix;

	// Set by rigidbody
	float intertia;  // moment of inertia
	float inverseInertia; // inverse inertia
	float mass;  // mass
	float inverseMass; // inverse masee

	float staticFriction;
	float dynamicFriction;
	float restitution;

	RigidBodyData(Vec2 velocity, float angularVelocity, float torque, Vec2 force, float staticFriction, float dynamicFrication, float restituation)
		: velocity(velocity), angularVelocity(angularVelocity), torque(torque), force(force), 
		staticFriction(staticFriction), dynamicFriction(dynamicFrication), restitution(restituation)
	{

	}
};

struct Rect
{
public:
	int xPos;
	int yPos;
	int width;
	int height;

	int colliderIndex;

	Rect() { }
	Rect(int x, int y, int wid, int hei, int colIndex = -1) : xPos(x), yPos(y), width(wid), height(hei), colliderIndex(colIndex) { }
};

struct ILevelData {};

struct LevelData : public ILevelData
{
public:
	int levelWidth;
	int levelHeight;

	float playerXPos;
	float playerYPos;

	float levelLeftBounds;
	float levelRightBounds;

	float levelBottomBounds;
	float levelTopBounds;
};

#pragma endregion
