#include "Player.h"
#include <random>
#include <cmath>
#include "../CsvData/DataClass/PlayerData.h"
#include "../CsvData/CsvDataManager.h"


// 각 값은 해당 함수가 끝난 후 결과값
//														      외부 입력 +
//                    IonStartI 다음 루프ㅣ 공격 주기 끝 ㅣ 공격 대기시간 I  패턴 변경 I
//  isPathenChange    I   T   I    F	  I     F         I      F        I    T       I 
//  isPattenCooldoown I   F   I    T      I     F		  I      F        I    F	   I
//. isPlayingPath     I   F   I	   F      I     T         I      F        I    F       I
//



void Player::OnStart() {
	//플레이어 상태 설정

	// 쿨타임 + 패턴 설정
	SelectPatten(); // 공격을 했으면 다른 패턴 세팅
	SetCoolTime();  // 쿨타임 다시 설정


} 



// 업데이트에서 시간 받기???? -> 필요없음, 수정하기!!!
void Player::OnUpdate(){

	CalSpiritTime();		// 1초마다 기세게이지 감소
}







//이후 StateManager에 추가하는거 만들기
void Player::SetState(std::string setStateName) { 
	m_State.SetState(setStateName);
}

void Player::OnCreateState() {
	m_State.CreateState("Player_Idle");    // 평소 상태     

	m_State.CreateState("Player_AttackSuccess"); // 공격 성공
	m_State.SetNextState("Player_AttackSuccess", "Player_Idle");
	m_State.SetTransitionTime("Player_AttackSuccess", 1.0f);

	m_State.CreateState("Player_AttackFail");  // 공격 실패
	m_State.SetNextState("Player_AttackFail", "Player_Idle");
	m_State.SetTransitionTime("Player_AttackFail", 1.0f);

	m_State.CreateState("Player_Hit");     //패턴 파회 X, 맞음
	m_State.SetNextState("Player_Hit", "Player_Idle");
	m_State.SetTransitionTime("Player_Hit", 1.0f);

	m_State.CreateState("Player_Defence"); //패턴 파회 X, 막음
	m_State.SetNextState("Player_Defence", "Player_Idle");
	m_State.SetTransitionTime("Player_Defence", 1.0f);

	m_State.CreateState("Player_Guard");   // 패턴 파회 O
	m_State.SetNextState("Player_Guard", "Player_Idle");
	m_State.SetTransitionTime("Player_Guard", 1.0f);

	m_State.CreateState("Player_Perry");   // 패턴 파회 O + 특정 시간 안에
	m_State.SetNextState("Player_Perry", "Player_Idle");
	m_State.SetTransitionTime("Player_Perry", 1.0f);
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
	Object_nowCoolTime = 0.0f;									 //
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


// 플래그를 정하는 함수
void Player::ChangePatten() {
	// 패턴이 바뀌었으면 isPattenChange   : T, 다음 루프에 F
	//                   isPattenCooldown : T
	if (prePlayerPattenData != nowPlayerPattenData) {
		prePlayerPattenData = nowPlayerPattenData;
		isPattenChange = true;
	}
	else {
		isPattenChange = false;
	}

	if (!isPattenChange) {
		isPlayingPatten = true;
	}
	
	// 패턴의 입력시간이 다 되거나 외부에 입력에 의해서 종료되면 isPlayingPatten : F
	// 패턴의 입력시간이 줄어드는 중이면 isPlayingPatten : T

	if (isPlayingPatten) {
		// 패턴의 입력대기시간 감소
		Object_nowPlayingAttackTime += SceneDeltaTime;

		if (Object_nowPlayingAttackTime >= Object_PlayingAttackTime) {
			isPlayingPatten = false;
		}
		
	}
	else {
		Object_nowPlayingAttackTime  = 0.0f;
	}
	

	//위의 3가지 플래그가 모두 F -> 패턴 변경 -> 다음 루프 -> isPattenChange =  T
	if(!isPattenChange || !isPattenCooldown || !isPlayingPatten){
		m_State.SetState("Player_AttackFail");
		SelectPatten();
	}

}

void DeciedState(const std::queue<int> tmpqueue);  //큐와 현재 패턴을 비교
void CalStat();        //여기서 계산


