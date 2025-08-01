#pragma once
#include "LiveObject.h"
#include "../CsvData/DataClass/EnemyData.h"


class LiveObject;
class Enemy : public LiveObject
{
public:
	Enemy() {};
	~Enemy() {};
public:
	std::string GetDifficulty() override { return Difficulty; } // 난이도 반환
	void SetAllData(std::string tmp);

	void SelectPatten();   //각 객체가 사용할 패턴을 고름
	void CalCooTime();     //각 객체의 쿨타임을 계산
	void DeciedState(const std::queue<int> tmpqueue);  //큐와 현재 패턴을 비교
	void CalStat();        //여기서 계산


private:
	std::string Difficulty;			   // 적의 난이도 
	EnemyData* nowEnemyData = nullptr; // 현재 적의 데이터 클래스를 담을 변수

};

