#include "Enemy.h"
#include "../CsvData/CsvDataManager.h"


// 매개변수를 통해 데이터의 키값을 받아서 데이터를 찾고 데이터의 값을 적에게 전부 인가
void Enemy::SetAllData(std::string tmp) {
	nowEnemyData = CsvDataManager::GetInstance().getDataImpl(nowEnemyData, tmp);
	Object_ID = nowEnemyData->enemyID;					   // ID
	Object_Name = nowEnemyData->enemyName;				   // 이름
	Object_Hp = nowEnemyData->enemyHealth;		           // 체력
	Object_Attack = nowEnemyData->enemyDamage;			   // 공격력
	Object_SpiritAttack = nowEnemyData->enemySpiritdamage; // 기세 공격력
	Object_DefenseRate = nowEnemyData->enemyGuardRate;	   // 방어율
	Object_SpiritAmount = nowEnemyData->enemySpiritamount; // 기세
	Difficulty = nowEnemyData->enemyDifficulty;			   // 난이도 -> 아마 필요없을듯?
}
