#include "BettleManager.h"
#include <cmath>
#include "../LiveObject/Player.h"
#include "../LiveObject/Enemy.h"
#include "../LiveObject/LiveObject.h"
#include "AttackPatternManager.h"
#include "Components/Base/GameObject.h"
#include "Components/Base/MonoBehavior.h"
#include "Scripts/GameManager.h"
#include "Math/GameRandom.h"


/// 상태 정리
/// m_State->CreateState("Player_Idle");    // 평소 상태     
/// 
/// m_State->CreateState("Player_AttackSuccess"); // 공격 성공
/// m_State->SetNextState("Player_AttackSuccess", "Player_Idle");
/// m_State->SetTransitionTime("Player_AttackSuccess", 1.0f);
/// 
/// m_State->CreateState("Player_AttackFail");  // 공격 실패
/// m_State->SetNextState("Player_AttackFail", "Player_Idle");
/// m_State->SetTransitionTime("Player_AttackFail", 1.0f);
/// 
/// m_State->CreateState("Player_Hit");     //패턴 파회 X, 맞음
/// m_State->SetNextState("Player_Hit", "Player_Idle");
/// m_State->SetTransitionTime("Player_Hit", 1.0f);
/// 
/// m_State->CreateState("Player_Defence"); //패턴 파회 X, 막음
/// m_State->SetNextState("Player_Defence", "Player_Idle");
/// m_State->SetTransitionTime("Player_Defence", 1.0f);
/// 
/// m_State->CreateState("Player_Guard");   // 패턴 파회 O
/// m_State->SetNextState("Player_Guard", "Player_Idle");
/// m_State->SetTransitionTime("Player_Guard", 1.0f);
/// 
/// m_State->CreateState("Player_Perry");   // 패턴 파회 O + 특정 시간 안에
/// m_State->SetNextState("Player_Perry", "Player_Idle");
/// m_State->SetTransitionTime("Player_Perry", 1.0f);
/// 
/// m_State->CreateState("Player_Groggy");   // 패턴 파회 O + 특정 시간 안에
/// m_State->SetNextState("Player_Groggy", "Player_Idle");
/// m_State->SetTransitionTime("Player_Groggy", 2.0f);
/// 
/// m_State->CreateState("Player_Dead");   // 죽음


void BettleManager::OnStart() 
{
	// 플레이어 기세 값 설정
	m_Player->SetSpiritData(m_Enemy->GetSpiritAmount());	

	// AttackPatternManager 찾기
	m_PattenManager = owner->GetQuery()->FindByName("AttackPattenManager")->GetComponent<AttackPatternManager>(); 

	// 이전 기세 량 초기화
	preSpiritAmount = m_Player->GetNowSpiritAmount();

	// 게이지 스크립트 등록
	owner->AddComponent<GiseGauge>();
	giseObj = owner->GetComponent<GiseGauge>();

	giseTotalValue = m_Player->GetSpiritAmount();
	/*giseObj->SetMaxGague(TotalValue);*/

	//HpObj = owner->AddComponent<HpGauge>();
	////HP 최대치 설정 플레이어, 적
	//HpObj->SetPlayerMaxGague(m_Player->GetTotalHp());
	//HpObj->SetEnemyMaxGague(m_Enemy->GetTotalHp());



	/*HpObj->SetHpUiPosition(Player, Enemy);*/
}

void BettleManager::OnUpdate() 
{
	SetSpiritGauge();		  // 기세 게이지 업데이트
	SetGroggyState();         // 그로기 스테이트 업데이트
	ChangeCommonFinalState(); // 
	if (!m_Player->GetIsGroggy() && !m_Enemy->GetIsGroggy()) {
		SetStateFormPatternIdle();
		ChangeFinalStateIdle();
	}		
	else {
		if (m_Enemy->GetIsGroggy()) {  // 적이 그로기 상태일때
			SetStateFormPatternEnemyGroggy();
			SetAnimationAtOtherGroggy();
			ChangeFinalStateEnemyGroggy();


		}
		else if (m_Player->GetIsGroggy()) { // 플레이어가 그로기 상태일 때
			SetStateFormPatternPlayerGroggy();
			ChangeFinalStatePlayerGroggy();


		}
	}

	//HpObj->SetHpUiPosition(Player2, Enemy2);
	/*HpObj->CalculatePlayerValue(m_Player->GetHp());
	HpObj->CalculateEnemyValue(m_Enemy->GetHp());*/
    
	// 게임 상태가 Pause면 모든 Update 내용 무시
	if (Singleton<GameManager>::GetInstance().GetGameState() == GameState::Pause)
	{
		return;
	}

	// 이거 밑에 2개 정의안된듯?
	//ChangeFinalState();		// 각 LiveObject의 사망 처리 Update - 유니티의 AnyState 유사
	SetGroggyState();

	//SetStateFormPattern();	// 각 상태별 공격 방어 처리 어

	ResetState(); 			// state가 다를 경우 초기화 하기!!!
}





float BettleManager::ConvertHPDamageToPos(AttackPosition lastPos, float HpDamage)
{
	switch (lastPos)
	{
	case UpNode:      return  HpDamage * 1.25f;    // 상단 노드일때 1.25배 추가뎀
	case MiddleNode:  return  HpDamage;            // 중단 노드
	case LowNode:     return  HpDamage * 0.75f;    // 하단 노드
	default:		  return  0.0f;
	}
}

float BettleManager::ConvertSpiritDamageToPos(AttackPosition lastPos, float SpiritDamage)
{
	switch (lastPos)
	{
	case UpNode:      return SpiritDamage * 0.75f;  // 상단 노드일때  0.75배 뎀감
	case MiddleNode:  return SpiritDamage;			// 중단 노드
	case LowNode:     return SpiritDamage * 1.25f;  // 하단 노드
	default:		  return 0.0f;
	}
}

// 하드코딩용 : 입력 패턴 고정

// 노드 인풋 - Pattern Manager에서 사용
void BettleManager::SetInputNode(std::vector<int> InputNode) 
{
	nowNode = InputNode;
}

//들어온 입력 노드에 따라서 공격, 방어를 처리하는 함수




void BettleManager::SetStateFormPatternPlayerGroggy() // 플레이어 그로기 상태에 패턴 검색
{
	m_PattenManager->PlayerPatternAllClear();
	SetStateFormPatternIdle(); 
}

void BettleManager::SetStateFormPatternEnemyGroggy()// 적 그로기 상태에 패턴 검색
{
		// 모든 패턴 제거
	m_PattenManager->EnemyPatternAllClear();
	m_PattenManager->PlayerPatternAllClear();
	m_PattenManager->DoneTimeOutPatten();
	if (nowNode.size() < 2) return; // 플레이어가 입력을 하기 전까지 빠져나가질 못함 (8.12 확인)
	if (allDistancePercent <= 0.001f) //퍼센트가 0 이라면 길이에 따라서 배율 넣기 , 문제 있을 수 있음
	{
		// 연격 패턴 이벤트 호출
		onFinalBlow.Invoke(); // 외부에 공격 준비를 알림(총알이 장전된거임)
		allDistancePercent = m_PattenManager->OnceAllNodePatternDistance(nowNode); // 연격 길이 퍼센트 반환
	}

	tmpAttackNode = nowNode;   //연격을 임시 벡터에 저장!!
	nowNode.clear();
}


//분리는 나중에.......

void BettleManager::SetStateFormPatternIdle() 
{
	// 플레이어와 적 모두가 그로기 상태가 아니면
		nowManagerState = noneGroggy;
		std::unordered_map<std::string, pattern*> tmpTimePatten = m_PattenManager->TimeOutPatten();  // 패턴의 시간이 만료되었으면 
		for (const auto& pair : tmpTimePatten) 
		{
			if (pair.second->PattenID.substr(0, 2) == "EP") // 적 패턴일 때
			{
				m_Enemy->SetState("Enemy_AttackSuccess");  // 적 상태 변경 -> 적 공격 성공

				// 마지막 노드가 중앙 노드가 아니면 일정 확률로 회피
				if (m_Player->GetDefenseRate() >= GameRandom::RandomRange(1, 101) && pair.second->lastPosition != MiddleNode) 
				{
					m_Player->SetState("Player_Defence");			 // 플레이어 상태 변경 -> 플레이어 회피
				}
				else // 회피 실패
				{
					m_Player->SetState("Player_Hit");   			// 플레이어 상태 변경 -> 플레이어 피격
					m_Player->GetDamage(ConvertHPDamageToPos(pair.second->lastPosition, m_Enemy->GetAttack())); // 상중하 적용한 데미지
				}

				// 기세 계산
				
				if (m_Player->GetIsGroggy()) {
					m_Player->GetDamage(ConvertSpiritDamageToPos(pair.second->lastPosition, m_Enemy->GetSpiritAttack()));		// 플레이어는 데미지 받음
				}
				else {
					m_Enemy->RestoreSpiritDamage(ConvertSpiritDamageToPos(pair.second->lastPosition, m_Enemy->GetSpiritAttack()));	// 적은기세를 회복
					m_Player->GetSpiritdamage(ConvertSpiritDamageToPos(pair.second->lastPosition, m_Enemy->GetSpiritAttack()));		// 플레이어는 기세를 잃음
				}
				
			
			}
			m_PattenManager->SubPattern(pair.second->PattenID, "Time"); // 시간 종료된 패턴 제거
		}

		if (nowNode.size() < 1) return; // 플레이어가 입력한 노드가 없으면 무시

		pattern* tmpCorPatten = m_PattenManager->CorrectPattern(nowNode); // 현재 들어온 노드 index들

		// 입력이 적, 플레이어의 패턴과 맞을 경우
		if (tmpCorPatten != nullptr) 
		{
			if (tmpCorPatten->PattenID.substr(0, 2) == "EP") // 적 노드일 때
			{
				m_Enemy->SetState("Enemy_AttackSuccess");				// 적 상태 변경 -> 적 공격 성공
				if ((tmpCorPatten->PlayingAttackTime) <= 0.5f)			// 플레이어가 0.5초 이내에 가드시 -> 패링
				{  
					std::vector<int> tmp = tmpCorPatten->NodePatten;	// 플레이어 입력한 노드
					tmp.erase(std::remove(tmp.begin(), tmp.end(), 0), tmp.end());

					onParry.Invoke(tmp.front());		// 패링 이벤트 델리게이트 호출

					m_Player->SetState("Player_Perry"); // 플레이어 상태 변경 -> 플레이어 패링 상태

					// 패링에 따른 기세값 반영
					if (!m_Player->GetIsGroggy()) {
						m_Player->RestoreSpiritDamage(ConvertSpiritDamageToPos(tmpCorPatten->lastPosition, m_Enemy->GetSpiritAttack()));
						m_Enemy->GetSpiritdamage(ConvertSpiritDamageToPos(tmpCorPatten->lastPosition, m_Enemy->GetSpiritAttack()));
					}

					

				}
				else // 플레이어 패링 실패
				{
					std::vector<int> tmp = tmpCorPatten->NodePatten;
					tmp.erase(std::remove(tmp.begin(), tmp.end(), 0), tmp.end());
					onGuard.Invoke(tmp.front());

					m_Player->SetState("Player_Guard");		// 플레이어 상태 변경 -> 플레이어 방어

					// 패링 실패에 따른 기세값 변경
					if (m_Player->GetIsGroggy()) {
						m_Player->GetDamage(ConvertSpiritDamageToPos(tmpCorPatten->lastPosition, m_Enemy->GetSpiritAttack()));
					}
					else{
						m_Enemy->RestoreSpiritDamage(ConvertSpiritDamageToPos(tmpCorPatten->lastPosition, m_Enemy->GetSpiritAttack()));
						m_Player->GetSpiritdamage(ConvertSpiritDamageToPos(tmpCorPatten->lastPosition, m_Enemy->GetSpiritAttack()));
					}
				}
				
				m_PattenManager->SubPattern(tmpCorPatten->PattenID, "Enemy"); // 적 패턴 제거
			}
			else // 플레이어 공격 노드 - 패턴 이름이 PI_ 일 때
			{
				m_Player->SetState("Player_AttackSuccess");	// 플레이어 상태 변경 -> 플레이어 공격 성공
				m_Player->SetEndAttack();					// isAttackingPattern = true 

				// 마지막 노드가 중앙이 아니라면 적이 일정 확률로 회피 
				if (m_Enemy->GetDefenseRate() >= GameRandom::RandomRange(1, 101) && tmpCorPatten->lastPosition != MiddleNode)
				{
					m_Enemy->SetState("Enemy_Defence");	// 적 상태 변경 -> 적 회피
				}
				else // 적 회피 실패
				{
					m_Enemy->SetState("Enemy_Hit");		// 적 상태 변경 -> 적 피격
					m_Enemy->GetDamage(ConvertHPDamageToPos(tmpCorPatten->lastPosition, m_Player->GetAttack())); // 적 체력 감소
				}

				// 플레이어 공격에 따른 기세 값 변경
				m_Player->RestoreSpiritDamage(ConvertSpiritDamageToPos(tmpCorPatten->lastPosition, m_Player->GetSpiritAttack()));
				m_Enemy->GetSpiritdamage(ConvertSpiritDamageToPos(tmpCorPatten->lastPosition, m_Player->GetSpiritAttack()));

				// 플레이어 공격 가이드 패턴 ( A, B ) 파괴 - 점선 화살표 이미지
				m_PattenManager->SearchAndDestroyCouple(tmpCorPatten->PattenID);
				m_PattenManager->SubPattern(tmpCorPatten->PattenID, "Player");
			}
		}
		else // 입력이 생성된 가이드라인 또는 적 공격과 다른 경우 
		{
			pattern* tmpPatten = m_PattenManager->failPattern(nowNode);	// 입력한 플레이어 노드 인덱스 목록
			if (tmpPatten != nullptr) // 실패한 패턴이 있는 경우
			{   
				if (tmpPatten->PattenID.substr(0, 2) == "EP")			// 적 공격에 관한 실패
				{
					m_Enemy->SetState("Enemy_AttackSuccess");			// 적 공격 성공

					// 플레이어 회피
					if (m_Player->GetDefenseRate() >= GameRandom::RandomRange(1, 101))
					{
						m_Player->SetState("Player_Defence");			// 플레이어 상태 변경 -> 플레이어 회피
					}
					else 
					{
						m_Player->SetState("Player_Hit");   			// 플레이어 상태 변경 -> 플레이어 피격됨 
						m_Player->GetDamage(ConvertHPDamageToPos(tmpPatten->lastPosition, m_Enemy->GetAttack()));
					}

					// 기세 계산
					if (!m_Player->GetIsGroggy()){
						m_Player->RestoreSpiritDamage(ConvertSpiritDamageToPos(tmpPatten->lastPosition, m_Player->GetSpiritAttack()));
						m_Enemy->GetSpiritdamage(ConvertSpiritDamageToPos(tmpPatten->lastPosition, m_Player->GetSpiritAttack()));
					}
					

					// 사용된 적 패턴 제거
					m_PattenManager->SubPattern(tmpPatten->PattenID, "Enemy");
				}
				else // 플레이어 가이드 라인에 관한 실패
				{
					m_Player->SetState("Player_AttackFail");	// 플레이어 상태 변경 -> 플레이어 공격 실패
					m_Player->SetEndAttack();					// isAttackingPattern = true -> ??

					// 플레이어 가이드 패턴 파괴
					m_PattenManager->SearchAndDestroyCouple(tmpPatten->PattenID);
					m_PattenManager->SubPattern(tmpPatten->PattenID, "Player");
				}
			}
		}
	nowNode.clear(); // 플레이어 입력 노드 초기화
}



void BettleManager::ChangeFinalStateIdle()  //평소 상태에서  적과 플레이어의 상태를 변하게 하는 함수
{

}


void BettleManager::ChangeFinalStateEnemyGroggy()  // 적의 그로기 상태에서 적과 플레이어의 상태를 변하게하는 함수
{
	if (!m_Player->IsOtherGroggy) {
		m_Player->IsOtherGroggy = true;
		
	}

	if (isPlayingAni) { // 초기화 하기!!
		m_Player->OtherGroggyTimeStop = true;
	}
	else {
		m_Player->OtherGroggyTimeStop = false;
	}

	
	if (m_Player->isOtherGroggyEnd) {
		m_Player->isOtherGroggyEnd = false;
	}

	
}


void BettleManager::SetAnimationAtOtherGroggy() {
	if (tmpAttackNode.size() < 2) return;

	const float total = 1.5f;                                // 전체 재생 시간
	const int   steps = static_cast<int>(tmpAttackNode.size() - 1); // 스텝 개수
	const float aniTerm = total / steps;                      // 스텝 간격(초)

	AniTime += GameTime::GetInstance().GetDeltaTime();

	static int stepIdx = -1; // 직전 적용한 스텝 인덱스(프레임 간 유지)

	if (AniTime < total) {
		isPlayingAni = true;

		// 현재 스텝(0 ~ steps-1)
		int curStep = static_cast<int>(AniTime / aniTerm);
		if (curStep >= steps) curStep = steps - 1;

		// 스텝이 바뀌었을 때만 이미지 교체
		if (curStep != stepIdx) {
			stepIdx = curStep;
			m_Player->AttackAniSelect(stepIdx % 4); // 필요하면 다른 매핑으로 변경
		}
	}
	else {
		// 재생 종료 및 리셋
		isPlayingAni = false;
		AniTime = 0.0f;
		stepIdx = -1;
		tmpAttackNode.clear();
	}
	
}


void BettleManager::ChangeFinalStatePlayerGroggy() // 아군의  그로기 상태에서 적과 플레이어의 상태를 변하게 하는 함수 
{
	if (m_Player->GetIsGroggy() && !m_Enemy->IsOtherEndGroggy)
	{
		m_Enemy->IsOtherGroggy = true;
	}

	if (m_Enemy->IsOtherEndGroggy) {
		m_Enemy->IsOtherEndGroggy = false; 
		m_Enemy->IsOtherGroggy = false; 

		m_Player->RestoreGroggy();
	}
	
	
}



// State정하기
//그로기 + 죽음
void BettleManager::ChangeCommonFinalState() 
{
	
	// 플레이어 사망 확인
	if (m_Player->GetHp() <= 0.0f)
	{
		m_Player->SetState("Player_Dead");
	}

	// 적 사망 확인
	if (m_Enemy->GetHp() <= 0.0f)
	{
		m_Enemy->SetState("Enemy_Dead");
	}


	// 적과 아군 둘중 그로기가 끝나고 회복해야한다면
	if (m_Enemy->GetIsRestore() || m_Player->GetIsRestore()) 
	{
		m_Enemy->ResetSpiritAmount();  // 서로 기세게이지가 절반으로 돌아감
		m_Player->ResetSpiritAmount();
		m_Enemy->SetIsRestore(false);  // 기세 게이지 회복 표시
		m_Player->SetIsRestore(false);
	}



	

}



void BettleManager::SetSpiritGauge() 
{
	giseObj->SetMaxGague(giseTotalValue);
	giseChangeValue = m_Player->GetNowSpiritAmount();
	giseObj->CalculateValue(giseChangeValue);
}

/// 아군 홀드 공격 완료!!!
void BettleManager::FinalAttackToEnemy() // 델리게이트로 외부에서 연결	
{ 
	// 적이 그로기 상태일 때
	if (m_Enemy->GetIsGroggy()) 
	{
		m_Enemy->GetDamage((m_Player->GetAttack() * allDistancePercent * 10.0f));  /// 나중에 적 hp 배율 따로 빼기!!!!
		m_Enemy->SetState("Enemy_Hit");				// 적 상태 변경 -> 적 피격

		m_Player->isOtherGroggyEnd = false;		// 적 그로기 상태 해제
		m_Player->SetState("Player_AttackSuccess");	// 플레이어 상태 변경 -> 공격 성공
		m_Enemy->SetIsRestore(true);
	}
}


void BettleManager::SetGroggyState() 
{
	if (m_Player->GetIsGroggy())		// 플레이어가 그로기 일 때
	{
		nowManagerState = playerGroggy;
	}
	else if (m_Enemy->GetIsGroggy())	// 적이 그로기 일 때
	{
		nowManagerState = enemyGroggy;
	}
	else if ((!m_Enemy->GetIsGroggy()) && (!m_Player->GetIsGroggy())) // 둘다 그로기 아닐 때
	{
		nowManagerState = noneGroggy;
	}
	else // 예외 처리
	{
		nowManagerState = noneGroggy;
	}

	// 상태에 변경이 있고 이전 상태가 적 그로기 상태면 
	if (preManagerState != nowManagerState && preManagerState == enemyGroggy)
	{
		allDistancePercent = 0.0f;
		isOncePatternAttack = false;
		onTimeout.Invoke(); // 외부에 그로기 지속 시간이 끝났다는걸 알림
	}




	preManagerState = nowManagerState;
}

void BettleManager::ResetState()
{

}

