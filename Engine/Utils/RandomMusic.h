#pragma once
#include "pch.h"
#include "Math/GameRandom.h"

class RandomMusic
{
public:
	static float RandomSound() { return GameRandom::RandomRange(0.0f, 2.0f); }
	static float RandomSound2() { return GameRandom::RandomRange(0.0f, 3.0f); }
};

