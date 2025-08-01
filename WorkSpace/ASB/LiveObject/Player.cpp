#include "Player.h"
#include "../CsvData/DataClass/PlayerData.h"
#include "../CsvData/CsvDataManager.h"

// 플레이어 데이터에는 기세가 없음으로 적을 생성 후, 기세를 매개변수에 넣어주기!!
void Player::SetStatData(std::string tmp,float enemy_SpiritAmount) {
	nowPlayerData = CsvDataManager::GetInstance().getDataImpl(nowPlayerData, tmp);
	Object_ID = nowPlayerData->Character_ID;					 // ID
	Object_Name = nowPlayerData->Character_name;				 // 이름
	Object_Hp = nowPlayerData->Character_helath;				 // 체력
	Object_Attack = nowPlayerData->Character_damage;			 // 공격력
	Object_SpiritAttack = nowPlayerData->Character_spritdamage;  // 기세 공격력
	Object_DefenseRate = nowPlayerData->Character_guard_rate;	 // 방어율
	Object_SpiritAmount = enemy_SpiritAmount / 2.0f;				 // 기세의 총량을 설정
	Object_BaseSpiritAmount = enemy_SpiritAmount / 2.0f;
	PattenID = CsvDataManager::GetInstance().GetIDData(nowPlayerPattenData); // 패턴 데이터의 ID를 미리 받음
}

//패턴 ID에 맞는 데이터를 포인터로 가리킴
void Player::SetAttackPattenData(std::string PattID) {
	nowPlayerPattenData = CsvDataManager::GetInstance().getDataImpl(nowPlayerPattenData, PattID);
}

//처음에 받은 기세 게이지로 복구
void Player::ResetSpiritAmount() {
	Object_SpiritAmount = Object_BaseSpiritAmount;
}
