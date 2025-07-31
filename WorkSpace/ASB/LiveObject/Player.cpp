#include "Player.h"
#include "../CsvData/DataClass/PlayerData.h"
#include "../CsvData/CsvDataManager.h"

// 플레이어 데이터에는 기세가 없음으로 적을 생성 후, 기세를 매개변수에 넣어주기!!
void Player::SetAllData(std::string tmp,float tmpObject_SpiritAmount) {
	nowPlayerData = CsvDataManager::GetInstance().getDataImpl(nowPlayerData, tmp);
	Object_ID = nowPlayerData->Character_ID;					 // ID
	Object_Name = nowPlayerData->Character_name;				 // 이름
	Object_Hp = nowPlayerData->Character_helath;				 // 체력
	Object_Attack = nowPlayerData->Character_damage;			 // 공격력
	Object_SpiritAttack = nowPlayerData->Character_spritdamage;  // 기세 공격력
	Object_DefenseRate = nowPlayerData->Character_guard_rate;	 // 방어율
	Object_SpiritAmount = tmpObject_SpiritAmount;				 // 기세의 총량을 설정
}

