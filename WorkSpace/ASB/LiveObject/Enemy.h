#pragma once
#include "LiveObject.h"

class Enemy : public LiveObject
{
public:
	Enemy() {};
	~Enemy() {};
public:
	float GetTotalImbalance() override { return TotalImbalance; };
	std::string GetDifficulty() override { return Difficulty; } // 난이도 반환

private:
	float TotalImbalance = 0.0f; // 적의 총 채간
	std::string Difficulty;       // 적의 난이도 
};

