#pragma once

#include <map>
#include <vector>

#include "Math.h"

#pragma region Values

class ApplicationValues
{
public:
	int			ScreenWidth;
	int			ScreenHeight;
	std::string	ResourcesPath;

	static ApplicationValues& Instance()
	{
		static ApplicationValues Instance;
		return Instance;
	}
};

#pragma endregion

#pragma region GamePlay Vals

// PLAYER //
static float PLAYER_PROJECTILE_DAMAGE = 20; // Default 20
static float PLAYER_PROJECTILE_SPEED = 50; // Default 50
static float PLAYER_SHOOT_KNOCKBACK = 5; // Default 5
static float PLAYER_LATERAL_MAX_SPEED = 500; // Default is 500

// AI //
static float AI_PROJECTILE_DAMAGE = 20; // Default 20
static float AI_PROJECTILE_SPEED = 50; // Default 50
static float AI_LATERAL_MAX_SPEED = 300; // Default is 300

static float GRAVITY_SCALE = 20.0f; // Default is 20
static Vec2 GRAVITY_VECTOR(0, 9.81f * GRAVITY_SCALE); // Default is 9.81 * SCALE

#pragma endregion

#pragma region Application Values

static constexpr int MAX_QUADTREE_OBJECTS = 10;
static constexpr int MAX_QUADTREE_LEVELS = 5;

static constexpr int MAX_POLY_VERTEX_COUNT = 64;

static constexpr float PI = 3.141592741f;

#pragma endregion

#pragma region Enums

enum EngineState
{
	eEditor,
	ePlayMode
};

enum GameState 
{
	eStartScreen,
	ePlayingGame,
	eWaitingOnGUIInput
};
enum LevelState
{
	ePlaying,
	eDead,
	eWon
};

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
	{ "MageWalk",		"\\Images\\mage_walk.dds" },
	{ "HumanWalk",		"\\Images\\human_walk.dds" },
	{ "Ball",			"\\Images\\ColourBall.dds" },
	{ "Pipe",			"\\Images\\NewPipe.dds" },
	{ "FinishFlag",		"\\Images\\checkered_flag.dds" },
	{ "GUIButton",		"\\Images\\GUI\\button.dds" },
	{ "BG_Sky",			"\\Images\\Backgrounds\\Sky_back_layer.dds" },
	{ "BG_Vegetation",	"\\Images\\Backgrounds\\Vegetation_layer.dds" },
	{ "BG_Ground",		"\\Images\\Backgrounds\\Ground_(front_layer).dds" },
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

struct Bounds
{
public:
	int xPos;
	int yPos;
	int width;
	int height;

	int colliderIndex;

	Bounds() { }
	Bounds(int x, int y, int wid, int hei, int colIndex = -1) : xPos(x), yPos(y), width(wid), height(hei), colliderIndex(colIndex) { }
};

struct Rect
{
public:
	int LeftX;
	int RightX;
	int TopY;
	int BotY;
	Vec2 Centre;
};

struct ILevelData {};

struct LevelData : public ILevelData
{
public:
	float levelLeftBounds;
	float levelRightBounds;

	float levelBottomBounds;
	float levelTopBounds;
};

#pragma endregion
