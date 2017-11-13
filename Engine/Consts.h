#pragma once

#include <map>
#include <vector>

#include "IEMath.h"

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
	UpdateDirection,
	AddForce
};

enum ColliderType 
{
	Circle,
	Square
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

struct Collider {

};

struct AABB : public Collider
{
	AABB() : centre(), width(), height() {}

	AABB(const Vec2 & center, const float & wid, const float & hei)
		: centre(center)
		, width(wid)
		, height(hei)
	{

	}

	Vec2 centre;
	float width;
	float height;
};

#pragma endregion
