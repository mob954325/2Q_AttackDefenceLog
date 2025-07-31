#pragma once
#include "LiveObject.h"

class Enemy : public LiveObject
{
public:
	Enemy() {};
	~Enemy() {};
public:
	float GetTotalImbalance() override { return TotalSpiritAmount; };
	std::string GetDifficulty() override { return Difficulty; } // 난이도 반환
	void SetAllData(std::string tmp);

private:
	float TotalSpiritAmount = 0.0f; // 적의 총 채간
	std::string Difficulty;       // 적의 난이도 
	EnemyData* nowEnemyData = nullptr; // 현재 적의 데이터 클래스를 담을 변수

};

