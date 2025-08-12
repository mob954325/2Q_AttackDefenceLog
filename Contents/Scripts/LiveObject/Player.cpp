#include "Player.h"
#include <random>
#include <cmath>
#include "../CsvData/DataClass/PlayerData.h"
#include "../CsvData/CsvDataManager.h"
#include "../LogicManager/AttackPatternManager.h"
#include "Components/Base/GameObject.h"
#include "Utils/GameTime.h"

// 출력 함수
#include <iostream>
#include <windows.h>
#include <thread>

#include "../Engine/Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "Scripts/GameManager.h"
#include "Math/GameRandom.h"

#include "Objects/Scenes/Stage/StageResult/StageResult.h"

// 각 값은 해당 함수가 출력 중일때, 각 플레그 변화
//														     
//                    IonStartI 다음 루프ㅣ 공격 노드추가ㅣ			    I
//  isPattenCooldoown I   F   I    T      I     F		  I      F      I  
//


void Player::OnStart()
{
	m_State = owner->GetComponent<StateController>();
	m_PattenManager = owner->GetQuery()->FindByName("AttackPattenManager")->GetComponent<AttackPatternManager>();

	SetStatData("CI_001");	// 플레이어 데이터 설정	
	SetBitmap();			// 비트맵 설정
	OnCreateState();		// 플레이어 상태 설정

	m_State->SetState("Player_Idle");	// 플레이어 상태 변경 -> idle

	isAttackingPattern = true;
}

void Player::ResetPlayer()
{
	isAttackingPattern = true;

	SelectPattern();				// 공격을 했으면 다른 패턴 세팅 - 
	SetNowPattern();
	SetState("Player_Idle");	// 플레이어 상태 변경 - idle
}

void Player::OnUpdate() {

	// 게임 상태가 Pause면 모든 Update 무시
	if (Singleton<GameManager>::GetInstance().GetGameState() == GameState::Pause)
	{
		return;
	}

	// 플레이어가 사망이나 그로기 상태가 아니면
	if (m_State->GetNowName() != "Player_Dead" && (!isGroggy))
	{
		CalSpiritTime();		// 1초마다 기세게이지 감소
		AddPattenLoop();		// 패턴을 추가하는 루프
	}

	PrintConsole();		// 콘솔 호출
	m_State->Update(); 	// 각 state별 추가로 정의된 행동 호출
	DiffState();  		// 이전상태와 현재상태를 결정하는 함수
	StateAct();   		// 각 state 별 행동 

	// 이전 상태 저장
	oneLoopPreStateName = nowStateName;

	if (m_State->GetNowName() == "Player_Dead") // 플레이어 사망 시 
	{
		ChecKChnageScene();
	}
}

//이후 StateManager에 추가하는거 만들기

void Player::SetState(std::string setStateName)
{
	if (!(m_State->GetNowName() == "Player_Dead" || m_State->GetNowName() == "Player_Groggy"))
	{
		m_State->SetState(setStateName);
	}
}

//state 생성
//평소에 줄여놓기!
void Player::OnCreateState()
{
	m_State->CreateState("Player_Idle");							// 평소 상태 - Default State

	m_State->CreateState("Player_AttackSuccess");					// 공격 성공
	m_State->SetNextState("Player_AttackSuccess", "Player_Idle");	// Player_AttackSuccess -> Player_Idle
	m_State->SetTransitionTime("Player_AttackSuccess", 1.0f);		// 1.0f 뒤 변경

	m_State->CreateState("Player_AttackFail");						// 공격 실패
	m_State->SetNextState("Player_AttackFail", "Player_Idle");		// Player_AttackFail -> Player_Idle
	m_State->SetTransitionTime("Player_AttackFail", 1.0f);			// 1.0f 뒤 변경

	m_State->CreateState("Player_Hit");								// 패턴 파회 X, 맞음
	m_State->SetNextState("Player_Hit", "Player_Idle");				// Player_Hit -> Player_Idle
	m_State->SetTransitionTime("Player_Hit", 1.0f);					// 1.0f 뒤 변경

	m_State->CreateState("Player_Defence");							// 패턴 파회 X, 막음
	m_State->SetNextState("Player_Defence", "Player_Idle");			// Player_Defence -> Player_Idle
	m_State->SetTransitionTime("Player_Defence", 1.0f);				// 1.0f 뒤 변경

	m_State->CreateState("Player_Guard");							// 패턴 파회 O
	m_State->SetNextState("Player_Guard", "Player_Idle");			// Player_Guard -> Player_Idle
	m_State->SetTransitionTime("Player_Guard", 1.0f);				// 1.0f 뒤 변경

	m_State->CreateState("Player_Perry");							// 패턴 파회 O + 특정 시간 안에
	m_State->SetNextState("Player_Perry", "Player_Idle");			// Player_Perry -> Player_Idle
	m_State->SetTransitionTime("Player_Perry", 1.0f);				// 1.0f 뒤 변경

	m_State->CreateState("Player_Groggy");							// 패턴 파회 O + 특정 시간 안에
	m_State->SetNextState("Player_Groggy", "Player_Idle");			// Player_Groggy -> Player_Idle
	m_State->SetTransitionTime("Player_Groggy", 2.0f);				// 2.0f 뒤 변경

	m_State->CreateState("Player_OtherGroggy");							// 패턴 파회 O + 특정 시간 안에
	m_State->SetNextState("Player_OtherGroggy", "Player_Idle");			// Player_Groggy -> Player_Idle
	m_State->SetTransitionTime("Player_OtherGroggy", 2.0f);				// 2.0f 뒤 변경

	m_State->CreateState("Player_Dead");							// 죽음
}

void Player::SetBitmap()
{
	player_Idle = owner->AddComponent<BitmapRenderer>();
	player_Idle->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\player_standing_fin.png");

	player_Attack1 = owner->AddComponent<BitmapRenderer>();
	player_Attack1->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\player_attack1_fin.png");

	player_Attack2 = owner->AddComponent<BitmapRenderer>();
	player_Attack2->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\player_attack2_fin.png");

	player_Attack3 = owner->AddComponent<BitmapRenderer>();
	player_Attack3->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\player_attack3_fin.png");


	player_Damaged = owner->AddComponent<BitmapRenderer>();
	player_Damaged->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\player_demaged_fin.png");

	player_Guard = owner->AddComponent<BitmapRenderer>();
	player_Guard->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\player_guard_fin.png");


	D2D1_SIZE_F size = player_Idle->GetResource()->GetBitmap()->GetSize(); // 크기 같음으로 그냥 해도 될듯?
	owner->GetTransform().SetOffset(-size.width / 2, size.height / 2);
	//owner->GetTransform().SetScale(0.9f, 0.9f); //  크기 맞추기
	owner->GetTransform().SetPosition(-450.0f, 50.0f);
}


// 플레이어 데이터에는 기세가 없음으로 적을 생성 후, 기세를 매개변수에 넣어주기!!
// 패턴을 세팅하는 것은 처음?
void Player::SetStatData(std::string tmp)
{
	nowPlayerData = CsvDataManager::GetInstance().getDataImpl(nowPlayerData, tmp);
	Object_ID = nowPlayerData->Character_ID;					 // ID
	Object_Name = nowPlayerData->Character_name;				 // 이름
	Object_Hp = nowPlayerData->Character_helath;				 // 체력
	Object_TotalHp = Object_Hp;									 // 전체 체력
	Object_Attack = nowPlayerData->Character_damage;			 // 공격력
	Object_SpiritAttack = nowPlayerData->Character_spritdamage;  // 기세 공격력
	Object_DefenseRate = nowPlayerData->Character_guard_rate;	 // 방어율

	PatternID = CsvDataManager::GetInstance().GetIDData(nowPlayerPattenData); // 패턴 데이터의 ID를 미리 받음

	Object_CoolTime = 1.0f;                                     //일단 쿨타임 1로 고정! -> 추후 변경가능
	Object_nowCoolTime = 1.0f;									 //
}

void Player::SetSpiritData(float enemy_SpiritAmount)
{
	Object_SpiritAmount = enemy_SpiritAmount;					 // 기세의 총량을 설정
	Object_NowSpiritAmount = enemy_SpiritAmount / 2.0f;
}

//패턴 ID에 맞는 데이터를 포인터로 가리킴
void Player::SetAttackPattenData(std::string PattID)
{
	nowPlayerPattenData = CsvDataManager::GetInstance().getDataImpl(nowPlayerPattenData, PattID);
};

// 플레이어의 가이드 패턴2개를 패턴매니저에 등록
void Player::SetNowPattern()
{
	std::vector<int> tmp;
	std::vector<int> tmp2;

	tmp.clear();
	tmp2.clear();

	std::string modifiedID1 = nowPlayerPattenData->Player_pattern_ID;
	std::string modifiedID2 = nowPlayerPattenData->Player_pattern_ID;

	modifiedID1.push_back('A');
	modifiedID2.push_back('B');

	// 첫 번째 패턴 데이터 가져오기
	tmpNode = CsvDataManager::GetInstance().getDataImpl(tmpNode, nowPlayerPattenData->Node_pattern01);
	if (tmpNode != nullptr)
	{
		tmp = tmpNode->Node_Number;
	}

	// 두 번째 패턴 데이터 가져오기
	tmpNode2 = CsvDataManager::GetInstance().getDataImpl(tmpNode2, nowPlayerPattenData->Node_pattern02);
	if (tmpNode2 != nullptr)
	{
		tmp2 = tmpNode2->Node_Number;
	}

	// 원래 100 자리에 공격 패턴이 떠있는 시간이 들어가나 플레이어는 없음으로 임의의 큰 숫자 100 을 넣음
	m_PattenManager->AddPattern(modifiedID1, 100.0f, tmp);
	m_PattenManager->AddPattern(modifiedID2, 100.0f, tmp2);
};



// 배틀 매니저에서 사용될 함수
void Player::SelectPattern()  // 각 객체가 사용할 패턴을 고름
{
	if (attackPlayerPatternIDFix.substr(0, 2) != "PI")
	{
		int patternSize = PatternID.size();
		SetAttackPattenData(PatternID[GameRandom::RandomRange(1, patternSize)]);
	}
	else
	{
		SetAttackPattenData(attackPlayerPatternIDFix);
	}
}



//처음에 받은 기세 게이지로 복구
void Player::ResetSpiritAmount()
{
	Object_NowSpiritAmount = Object_SpiritAmount / 2.0f;
}




void Player::SetCoolTime()
{

		// 공격 주기 * (1.25 - 0.5 * (현재 기세 / 기세 게이지))
		Object_nowCoolTime = (1.25f - Object_NowSpiritAmount / Object_SpiritAmount / 2.0f) * Object_CoolTime;
}


void Player::CalSpiritTime()
{
	if ((!isGroggy) && (!IsOtherGroggy)) {  // 적이나 내가 그로기 상태라면
		if (Object_OverTimeSpirit >= 1)
		{
			Object_NowSpiritAmount -= 0.3f;									 //초당 0.3씩 감소
			Object_OverTimeSpirit = std::fmod(Object_OverTimeSpirit, 1.0f);  //실수형 나머지 연산자
		}

		Object_OverTimeSpirit += GameTime::GetInstance().GetDeltaTime();
	}
}



void Player::DiffState()
{
	if (m_State->GetNowName() != nowStateName) // 값이 항상 다름
	{
		preStateName = nowStateName;
		nowStateName = m_State->GetNowName();
	}

	if (IsOtherGroggy) // 적과 나 둘중 1명이 그로기
	{
		if(!OtherGroggyTimeStop)
		enemyGroggyTime += GameTime::GetInstance().GetDeltaTime();
	}

	// 그로기 시간!!!
	// 10초가 지나거나
	if (enemyGroggyTime >= 10.0f)
	{
		isOtherGroggyEnd = true;  // 아군의 연격 시간이 끝났다는 것을 표시
		RestoreGroggy();
	}

	// 기세 게이지가 벗어나지 않게 고정!!!
	// 현재 플레이어의 기세 게이지가 0.0f
	// 한 번의 그로기에 restore 2번 되는 현상방지 
	if (isRestore) {
		isGroggy = false;
	}
	else if (Object_NowSpiritAmount <= 0.0f) // 기세 게이지
	{
		isGroggy = true;
		Object_NowSpiritAmount = 0.0f;
		
	}
	else // 0.0f 초과면 false
	{
		isGroggy = false;
	}
	// 
	if (Object_NowSpiritAmount >= Object_SpiritAmount)
	{
		Object_NowSpiritAmount = Object_SpiritAmount;
	}
}



// 공격이 끝나면 -> isAttackingPattern  :  T
// isPattenCooldown   : T  -> 쿨타임을 계산
// isPattenCooldown   : F  -> 계산 X


// 플래그를 정하는 함수
void Player::AddPattenLoop()
{
	// ??

	if (isAttackingPattern) // 플레이어의 패턴이 성공시 작동
	{
		SetCoolTime();
		isPattenCooldown = true;
		isAttackingPattern = false;
	}

	if (isPattenCooldown) // -> 
	{
		// 패턴의 입력대기시간 카운트
		Object_nowCoolTime -= GameTime::GetInstance().GetDeltaTime();

		// 현재 패턴의 시간이 0이거나 이하가 되면 쿨타임계산 X
		if (Object_nowCoolTime <= 0)
		{
			Object_nowPlayingAttackTime = 1.0f;
			SelectPattern();
			SetNowPattern();
			isPattenCooldown = false;
		}
	}
}

void Player::RestoreGroggy()
{
	enemyGroggyTime = 0.0f;
	IsOtherGroggy = false;

	// 복구 직후 다음 프레임에 다시 그로기 재진입을 막기 위한 처리
	isGroggy = false;          // 지금 당장 그로기 해제
	ResetSpiritAmount();       

	isRestore = true;          // 베틀매니저에서 공통 회복 흐름에 쓰는 플래그 (유지)

	ResetPlayer();             // 상태/쿨타임/패턴 초기화 (기존 로직)
	onTimeOut.Invoke();        // 외부 알림 (기존 로직)
}


//일단 임시로 스테이트마다 스프라이트 설정
void Player::StateAct()
{
	if (!OtherGroggyTimeStop) {
		if (nowStateName == "Player_Idle")
		{    // 평소 상태     
			player_Idle->SetActive(true);
			AttackStateSelect(false);
			player_Damaged->SetActive(false);
			player_Guard->SetActive(false);
		}
		else if (nowStateName == "Player_AttackSuccess" || nowStateName == "Player_AttackFail") // 공격 성공, 공격 실패
		{
			player_Idle->SetActive(false);
			AttackStateSelect(true);
			player_Damaged->SetActive(false);
			player_Guard->SetActive(false);
		}
		else if (nowStateName == "Player_Hit") //피격 + 그로기
		{
			player_Idle->SetActive(false);
			AttackStateSelect(false);
			player_Damaged->SetActive(true);
			player_Guard->SetActive(false);
		}
		else if (nowStateName == "Player_Guard" || nowStateName == "Player_Defence" || nowStateName == "Player_Perry") // 가드 + defence + 패링
		{
			player_Idle->SetActive(false);
			AttackStateSelect(false);
			player_Damaged->SetActive(false);
			player_Guard->SetActive(true);
		}
		else if (nowStateName == "Player_Dead") // 죽음
		{
			player_Idle->SetActive(false);
			AttackStateSelect(false);
			player_Damaged->SetActive(true);
			player_Guard->SetActive(false);
		}
	}
}


void Player::AttackStateSelect(bool AttackActive)
{
	if (oneLoopPreStateName == nowStateName) return;

	if (AttackActive) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(1, 3); // 1 ~ 10 사이의 정수
		int randomValue = dist(gen);
		switch (randomValue)
		{
		case 1:
			player_Attack1->SetActive(true);
			player_Attack2->SetActive(false);
			player_Attack3->SetActive(false);
			break;
		case 2:
			player_Attack1->SetActive(false);
			player_Attack2->SetActive(true);
			player_Attack3->SetActive(false);
			break;
		case 3:
			player_Attack1->SetActive(false);
			player_Attack2->SetActive(false);
			player_Attack3->SetActive(true);
			break;
		default:
			break;
		}
	}
	else {
		player_Attack1->SetActive(false);
		player_Attack2->SetActive(false);
		player_Attack3->SetActive(false);
	}
}

void Player::AttackAniSelect(int count) {
	// 1) 전부 끄기 (기본 화면 포함)
	player_Idle->SetActive(false);
	player_Attack1->SetActive(false);
	player_Attack2->SetActive(false);
	player_Attack3->SetActive(false);
	player_Guard->SetActive(false);
	player_Damaged->SetActive(false);

	// 2) 필요한 것만 켜기 (원하는 매핑대로)
	switch (count){
	case 0: // 1프레임
		player_Attack1->SetActive(true);
		break;
	case 1: // 2프레임
		player_Attack2->SetActive(true);
		break;
	case 2: // 3프레임
		player_Attack3->SetActive(true);
		break;
	case 3: // 마무리 포즈(가드 등)
		player_Guard->SetActive(true);
		break;
	default:
		// 범위를 벗어나면 기본(Idle)로 보이게 하려면 여기서 Idle을 켜도 됨
		break;
	}
}

// ===================================================================================
// Debug

void Player::SetCursorPosition(int x, int y)
{
	COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Player::PrintConsole() {

	//SetCursorPosition(0, 600);
	std::cout << "                                                " << std::endl;
	std::cout << "Player HP		      : " << Object_Hp << "                                                " << std::endl;
	std::cout << "Player Attack		      : " << Object_Attack << "                                                " << std::endl;
	std::cout << "Player SpiritAttack           : " << Object_SpiritAttack << "                                                " << std::endl;
	std::cout << "Player NowSpiritAmount        : " << Object_NowSpiritAmount << "                                                " << std::endl;
	std::cout << "Player Object_CoolTime	      : " << Object_CoolTime << "                                                " << std::endl;
	std::cout << "Player nowCoolTime	      : " << Object_nowCoolTime << "                                                " << std::endl;
	std::cout << "Player nowTotalCoolTime	      : " << Object_nowTotalCoolTime << "                                                " << std::endl;
	std::cout << "Player PlayingAttackTime      : " << Object_PlayingAttackTime << "                                                " << std::endl;
	std::cout << "Player nowState               : " << nowStateName << "                                                " << std::endl;
	std::cout << "Player preState               : " << preStateName << "                                                " << std::endl;
	std::cout << "Player PatternID               : ";
	if (nowPlayerPattenData != nullptr)
		std::cout << nowPlayerPattenData->Player_pattern_ID << "                                                " << std::endl;
	std::cout << "Player PattenNode01           :  ";
	if (tmpNode != nullptr) {
		for (int i = 0; i < tmpNode->Node_Number.size(); i++)
			std::cout << tmpNode->Node_Number[i] << ", ";
		std::cout << "                                 " << std::endl;
	}
	std::cout << "Player PattenNode02           :  ";
	if (tmpNode2 != nullptr) {
		for (int i = 0; i < tmpNode2->Node_Number.size(); i++)
			std::cout << tmpNode2->Node_Number[i] << ", ";
		std::cout << "                                   " << std::endl;
	}
}

void Player::ChecKChnageScene()
{
	timer += Singleton<GameTime>::GetInstance().GetDeltaTime();

	if (!isCreatedResult)
	{
		GameObject* obj = new GameObject();
		obj->SetRenderLayer(EngineData::RenderLayer::UI);
		auto comp = obj->AddComponent<StageResult>();
		comp->SetPanelState(ResultPanelState::Defeat);
		isCreatedResult = true;
	}

	if (timer >= maxTimer)
	{
		Singleton<SceneManager>::GetInstance().LoadScene(SceneCount::MENU);
	}
}