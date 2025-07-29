#pragma once
#include "LiveObject.h"

class Enemy : public LiveObject
{
public:
	Enemy() {};
	~Enemy() {};
public:
	float GetTotalImbalance() override ;

private:
	float TotalImbalance = 0.0f;
};

