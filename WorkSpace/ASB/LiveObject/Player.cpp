#include "Player.h"
#include <random>
#include <cmath>
#include "../CsvData/DataClass/PlayerData.h"
#include "../CsvData/CsvDataManager.h"

void Player::OnStart() {
	//플레이어 상태 설정
	SetState();

	// 쿨타임 + 패턴 설정
	SelectPatten(); // 공격을 했으면 다른 패턴 세팅
	SetCoolTime();  // 쿨타임 다시 설정
} 



// 업데이트에서 시간 받기????
void Player::OnUpdate(){
	if (isAttack == true) {  //공격을 했다면
		SelectPatten();		 // 다른 패턴 세팅
		SetCoolTime();       // 쿨타임 다시 설정
		isZeroCool = false;
	}
	else {
		CalCooTime();		 // 쿨타임을 텔타타임에 따라 차감
	}
	if (Object_CoolTime <= 0.0f) { isZeroCool = true; } //시간이 0보다 작거나 같으면 플래그 T

	CalSpiritTime();		// 1초마다 기세게이지 감소
}







//이후 StateManager에 추가하는거 만들기
void Player::SetState() {
	Object_State.push_back("Player_Idle");
	Object_State.push_back("Player_Attack");
	Object_State.push_back("Player_Guard");
	Object_State.push_back("Player_Hit");
	Object_State.push_back("Player_Down");
}


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



// 플레이어의 가이드 패턴2개를 1개의 벡터에 담아서 리턴
std::vector<int> Player::GetNowPatten() {
	AllNodePattenClass* tmpNode = nullptr;
	std::vector<int> tmp; // 저장한 벡터 선언

	tmpNode = CsvDataManager::GetInstance().getDataImpl(tmpNode, nowPlayerPattenData->Node_pattern01); //포인터에  패턴 1 주소 저장			
	for (int i = 0; i < 10; i++) {
		tmp.push_back(tmpNode->Node_Number[i]);  // 벡터에 값 저장
	}

	tmpNode = CsvDataManager::GetInstance().getDataImpl(tmpNode, nowPlayerPattenData->Node_pattern02); //포인터에  패턴 2 주소 저장
	for (int i = 0; i < 10; i++) {
		tmp.push_back(tmpNode->Node_Number[i]);   // ''
	}
	return tmp;
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



//처음에 받은 기세 게이지로 복구
void Player::ResetSpiritAmount() {
	Object_NowSpiritAmount = Object_SpiritAmount / 2.0f;
}




// 해댱 객체의 업데이트에 들어갈 함수들
void Player::CalCooTime() {//각 객체의 쿨타임을 계산            // 쿨타임이 0보다 작으면
	Object_nowCoolTime -= SceneDeltaTime;						   // 현재 쿨타임에서 지난 시간만큼 차감
};
void Player::SetCoolTime() {
	//  ( 1 + (현재기세 - 전체기세/2) / 전체기세 /2) * 해당 패턴의 전체 쿨타임
	Object_nowCoolTime = (Object_NowSpiritAmount - Object_SpiritAmount/0.5f ) / Object_SpiritAmount / 2 * Object_CoolTime;


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


