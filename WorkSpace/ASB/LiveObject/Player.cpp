#include "Player.h"
#include <random>
#include <cmath>
#include "../CsvData/DataClass/PlayerData.h"
#include "../CsvData/CsvDataManager.h"


// 플레이어 데이터에는 기세가 없음으로 적을 생성 후, 기세를 매개변수에 넣어주기!!
// 패턴을 세팅하는 것은 처음?
void Player::SetStatData(std::string tmp,float enemy_SpiritAmount) {
	nowPlayerData = CsvDataManager::GetInstance().getDataImpl(nowPlayerData, tmp);
	Object_ID = nowPlayerData->Character_ID;					 // ID
	Object_Name = nowPlayerData->Character_name;				 // 이름
	Object_Hp = nowPlayerData->Character_helath;				 // 체력
	Object_Attack = nowPlayerData->Character_damage;			 // 공격력
	Object_SpiritAttack = nowPlayerData->Character_spritdamage;  // 기세 공격력
	Object_DefenseRate = nowPlayerData->Character_guard_rate;	 // 방어율
	Object_SpiritAmount = enemy_SpiritAmount;					 // 기세의 총량을 설정
	Object_NowSpiritAmount = enemy_SpiritAmount / 2.0f;
	PattenID = CsvDataManager::GetInstance().GetIDData(nowPlayerPattenData); // 패턴 데이터의 ID를 미리 받음

	Object_CoolTime = 1.0f ;                                     //일단 쿨타임 1로 고정! -> 추후 변경가능
	Object_nowCoolTime = 1.0f;
}

//패턴 ID에 맞는 데이터를 포인터로 가리킴
void Player::SetAttackPattenData(std::string PattID) {
	nowPlayerPattenData = CsvDataManager::GetInstance().getDataImpl(nowPlayerPattenData, PattID);
}

//처음에 받은 기세 게이지로 복구
void Player::ResetSpiritAmount() {
	Object_NowSpiritAmount = Object_SpiritAmount / 2.0f;
}

// 배틀 매니저에서 사용될 함수
void Player::SelectPatten() {   //각 객체가 사용할 패턴을 고름
	// 난수 발생
	std::random_device rd;     
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<> dist(1, PattenID.size()); // 1 ~ 10 사이의 정수
	int randomValue = dist(gen);

	// 난수를 index로 ID를 찾고 그걸로 포인터에 해당 데이터 주소를 인가 
	SetAttackPattenData(PattenID[randomValue - 1]);
}



void Player::CalCooTime() {//각 객체의 쿨타임을 계산
	if (Object_nowCoolTime <= 0.0f) {SetCoolTime();}               // 쿨타임이 0보다 작으면
	Object_nowCoolTime -= SceneDeltaTime;						   // 현재 쿨타임에서 지난 시간만큼 차감
};
void Player::SetCoolTime() {
	 Object_nowCoolTime = Object_NowSpiritAmount / Object_SpiritAmount * 100.0f * Object_CoolTime;
}
void Player::CalSpiritTime() {
	if(Object_OverTimeSpirit >= 1){
		Object_NowSpiritAmount -= 0.3f;									 //초당 0.3씩 감소
		Object_OverTimeSpirit = std::fmod(Object_OverTimeSpirit, 1.0f);  //실수형 나머지 연산자
	}
	Object_OverTimeSpirit += SceneDeltaTime;
}


void DeciedState(const std::queue<int> tmpqueue);  //큐와 현재 패턴을 비교
void CalStat();        //여기서 계산