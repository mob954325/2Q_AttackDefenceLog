#include "Player.h"
#include <random>
#include <cmath>
#include "../CsvData/DataClass/PlayerData.h"
#include "../CsvData/CsvDataManager.h"
#include "../LogicTestManager/AttackPatternManager.h"
#include "Components/Base/GameObject.h"


// 각 값은 해당 함수가 출력 중일때, 각 플레그 변화
//														     
//                    IonStartI 다음 루프ㅣ 공격 노드추가ㅣ			    I
//  isPattenCooldoown I   F   I    T      I     F		  I      F      I  
//



void Player::OnStart() {
	m_State = owner->GetComponent<StateController<Player>>();
	SelectPatten(); // 공격을 했으면 다른 패턴 세팅
	SetCoolTime();  // 쿨타임 다시 설정
	isPattenCooldown = false;

}



// 업데이트에서 시간 받기???? -> 필요없음, 수정하기!!!
void Player::OnUpdate() {
	if (m_State->GetNowName() != "Player_Dead"){
		CalSpiritTime();		// 1초마다 기세게이지 감소
		AddPattenLoop();		// 패턴을 추가하는 루프
	}

	
}

//이후 StateManager에 추가하는거 만들기
void Player::SetState(std::string setStateName) { 
	m_State->SetState(setStateName);
}

void Player::OnCreateState() {
	m_State->CreateState("Player_Idle");    // 평소 상태     

	m_State->CreateState("Player_AttackSuccess"); // 공격 성공
	m_State->SetNextState("Player_AttackSuccess", "Player_Idle");
	m_State->SetTransitionTime("Player_AttackSuccess", 1.0f);

	m_State->CreateState("Player_AttackFail");  // 공격 실패
	m_State->SetNextState("Player_AttackFail", "Player_Idle");
	m_State->SetTransitionTime("Player_AttackFail", 1.0f);

	m_State->CreateState("Player_Hit");     //패턴 파회 X, 맞음
	m_State->SetNextState("Player_Hit", "Player_Idle");
	m_State->SetTransitionTime("Player_Hit", 1.0f);

	m_State->CreateState("Player_Defence"); //패턴 파회 X, 막음
	m_State->SetNextState("Player_Defence", "Player_Idle");
	m_State->SetTransitionTime("Player_Defence", 1.0f);

	m_State->CreateState("Player_Guard");   // 패턴 파회 O
	m_State->SetNextState("Player_Guard", "Player_Idle");
	m_State->SetTransitionTime("Player_Guard", 1.0f);

	m_State->CreateState("Player_Perry");   // 패턴 파회 O + 특정 시간 안에
	m_State->SetNextState("Player_Perry", "Player_Idle");
	m_State->SetTransitionTime("Player_Perry", 1.0f);

	m_State->CreateState("Player_Dead");   // 죽음
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



// 플레이어의 가이드 패턴2개를 패턴매니저에 등록
std::vector<int> Player::SetNowPatten() {
	AllNodePattenClass* tmpNode = nullptr;
	std::vector<int> tmp; // 저장한 벡터 선언
	std::vector<int> tmp2;
	std::string tmpID1 = nowPlayerPattenData->Node_pattern01;
	std::string tmpID2 = nowPlayerPattenData->Node_pattern02;
	tmpID1.push_back('1');
	tmpID2.push_back('2');
	tmpNode = CsvDataManager::GetInstance().getDataImpl(tmpNode, nowPlayerPattenData->Node_pattern01); //포인터에  패턴 1 주소 저장			
	for (int i = 0; i < 10; i++) {
		tmp.push_back(tmpNode->Node_Number[i]);  // 벡터에 값 저장
	}

	tmpNode = CsvDataManager::GetInstance().getDataImpl(tmpNode, nowPlayerPattenData->Node_pattern02); //포인터에  패턴 2 주소 저장			
	for (int i = 0; i < 10; i++) {
		tmp2.push_back(tmpNode->Node_Number[i]);  // 벡터에 값 저장
	}

	m_PattenManager.AddPattern(tmpID1, Object_nowCoolTime, tmp); // 패턴이 끝나는 시간이 따로 정해져있지 않음으로 플레이어의 공격 주기와 일치!
	m_PattenManager.AddPattern(tmpID2, Object_nowCoolTime, tmp2);
}



// 배틀 매니저에서 사용될 함수
void Player::SelectPatten() {   //각 객체가 사용할 패턴을 고름
	prePlayerPattenData = nowPlayerPattenData;
	while(1) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(1, PattenID.size()); // 1 ~ 10 사이의 정수
		int randomValue = dist(gen);
		SetAttackPattenData(PattenID[randomValue - 1]);
		if (prePlayerPattenData != nowPlayerPattenData)
			break;
	}
}





//처음에 받은 기세 게이지로 복구
void Player::ResetSpiritAmount() {
	Object_NowSpiritAmount = Object_SpiritAmount / 2.0f;
}



void Player::SetCoolTime() {
	//  ( 1 + (현재기세 - 전체기세/2) / 전체기세 /2) * 해당 패턴의 전체 쿨타임
	Object_nowCoolTime = (Object_NowSpiritAmount - Object_SpiritAmount/0.5f ) / Object_SpiritAmount / 2 * Object_CoolTime;

		if (prePlayerPattenData == nullptr) {  //이전 루프가 없을시
			// ( 1 + (현재기세 - 전체기세/2) / 전체기세 /2) * 해당 패턴의 전체 쿨타임
			Object_nowCoolTime = (Object_NowSpiritAmount - Object_SpiritAmount / 0.5f) / Object_SpiritAmount / 2 * Object_CoolTime;
		}
		else {  // 이전 루프가 있을 시
				//  ( 1 + (현재기세 - 전체기세/2) / 전체기세 /2) * 해당 패턴의 전체 쿨타임 + 이전 루프의 공격시간
			Object_nowCoolTime = (Object_NowSpiritAmount - Object_SpiritAmount / 0.5f) / Object_SpiritAmount / 2 * Object_CoolTime + 1.0f;
		}
		// 현재 공격중인 시간
		Object_PlayingAttackTime = 1.0f;
}
void Player::CalSpiritTime() {
	if(Object_OverTimeSpirit >= 1){
		Object_NowSpiritAmount -= 0.3f;									 //초당 0.3씩 감소
		Object_OverTimeSpirit = std::fmod(Object_OverTimeSpirit, 1.0f);  //실수형 나머지 연산자
	}
	Object_OverTimeSpirit += SceneDeltaTime;
}





// 플래그를 정하는 함수
void Player::AddPattenLoop() {
	// isPattenCooldown : T  -> 쿨타임을 계산
	// isPattenCooldown : F  -> 계산 X
	if(isPattenCooldown){
		// 패턴의 입력대기시간 카운트
		Object_nowPlayingAttackTime += SceneDeltaTime;
		// 현재 시간이  정해진 대기시간보다 크거나 같을 경우 
		if (Object_nowPlayingAttackTime >= Object_PlayingAttackTime) {
			isPattenCooldown = false;
		}
	}
	else{
		Object_nowPlayingAttackTime  = 0.0f;
		SelectPatten();  // 
		SetCoolTime();   // 적일때는 수정하기!!
		SetNowPatten();
	}
}



