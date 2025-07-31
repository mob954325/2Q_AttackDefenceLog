#pragma once
#include "BaseData.h"

/*2025.07.29 - 안성빈

    주의 : 적의 정보를 불러올 때, 필요한 ID가 다르거나 다른것을 기준으로도 할 수 있음 -> 추후 수정예정
*/ 
class EnemyData : public BaseData
{
public:
	EnemyData() {};
	~EnemyData() {};
	std::string enemyID;          // 적의 ID를 저장
	std::wstring enemyName;        // 적의 이름을 저장
	std::string enemyDifficulty;  // 적의 난이도를 저장   <- 중요!
	float enemyHealth;            // 적의 공격력을 저장
	float enemyDamage;            // 적의 방어력을 저장
	float enemyCooldown;          // 적의 공격 쿨타임을 저장
	float enemySpiritdamage;      // 적의 기세 공격력을 저 장
	float enemySpiritamount;	  // 기세의 총량을 저장   <- 중요!
	float enemyGuardRate;         // 적의 방어율을 저장
	std::vector<std::string> enemyPattern;    //적의 패턴을 저장
	//std::unordered_map<std::string, std::string> enemySprite;  // 적의 스프라이트를 저장


	void SetData(std::vector<std::wstring> tmp) override ; // 데이터 설정 함수
	void PrintMap() override ; // 콘솔창에 데이터 출력

};

