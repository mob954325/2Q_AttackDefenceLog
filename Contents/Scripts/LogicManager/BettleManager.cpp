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
#include "Objects/Sound/SoundPlayScene.h"
#include "../Contents/Scripts/Camera/CamInstance.h"


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

void BettleManager::OnCreate()
{

}

void BettleManager::OnStart()
{
	// 플레이어 기세 값 설정
	m_Player->SetSpiritData(m_Enemy->GetSpiritAmount());
	// 플레이어 기세 감소 값 설정
	m_Player->SetSpriteDamageSecond(m_Enemy->eSpriteDamage_Second);



	// AttackPatternManager 찾기
	m_PattenManager = owner->GetQuery()->FindByName("AttackPattenManager")->GetComponent<AttackPatternManager>();

	// 이전 기세 량 초기화
	preSpiritAmount = m_Player->GetNowSpiritAmount();



	// 게이지 스크립트 등록
	owner->AddComponent<GiseGauge>();
	giseObj = owner->GetComponent<GiseGauge>();

	giseTotalValue = m_Player->GetSpiritAmount();
	//giseObj->SetMaxGague(m_Player->GetTotalHp());

	InitHpGauge();

}

void BettleManager::OnUpdate()
{
	SetSpiritGauge();		  // 기세 게이지 업데이트
	SetGroggyState();         // 그로기 스테이트 업데이트
	
	if (!m_Player->GetIsGroggy() && !m_Enemy->GetIsGroggy()) {
		SetStateFormPatternIdle();
		ChangeFinalStateIdle();
		usedStartBlow = false;
	}
	else {
		if (m_Enemy->GetIsGroggy()) {  // 적이 그로기 상태일때
			SetStateFormPatternEnemyGroggy();
			//여기 개수대로 이팩트 출력!!
			SetAnimationAtOtherGroggy();
			ChangeFinalStateEnemyGroggy();

			if (!usedStartBlow) { // 상태에 처음 진입했을때만 켜짐
				onStartBlow.Invoke();
				usedStartBlow = true;
			}

		}
		else if (m_Player->GetIsGroggy()) { // 플레이어가 그로기 상태일 때
			SetStateFormPatternPlayerGroggy();
			ChangeFinalStatePlayerGroggy();

			if (!usedStartBlow) {
				onStartEnemyBlow.Invoke();
				usedStartBlow = true;
			}

		}
	}

	HpObj->CalculatePlayerValue(m_Player->GetHp());
	HpObj->CalculateEnemyValue(m_Enemy->GetHp());

	ChangeCommonFinalState(); // 
	// 게임 상태가 Pause면 모든 Update 내용 무시
	if (Singleton<GameManager>::GetInstance().GetGameState() == GameState::Pause)
	{
		return;
	}

	// 이거 밑에 2개 정의안된듯?
	//ChangeFinalState();		// 각 LiveObject의 사망 처리 Update - 유니티의 AnyState 유사

	//SetStateFormPattern();	// 각 상태별 공격 방어 처리 어

	ResetState(); 			// state가 다를 경우 초기화 하기!!!

	
}

void BettleManager::InitHpGauge()
{
	HpObj = owner->AddComponent<HpGauge>();

	//HP 최대치 설정 플레이어, 적
	HpObj->SetPlayerMaxGague(m_Player->GetTotalHp());
	HpObj->SetEnemyMaxGague(m_Enemy->GetTotalHp());

	float playerOffsetX = EngineData::SceenWidth * 0.048f;
	float playerOffsetY = 0;

	float enemyOffsetX = EngineData::SceenWidth * 0.705f;
	float enemyOffsetY = 0;


	HpObj->SetHpUiPosition({ playerOffsetX, playerOffsetY }, { enemyOffsetX, enemyOffsetY });
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
	m_PattenManager->EnemyPatternAllClear();
	m_PattenManager->PlayerPatternAllClear();
	m_PattenManager->DoneTimeOutPatten();
	if (m_PattenManager->AtPlayerGroggyEnemyStorage.size() < 1)  return;
	m_PattenManager->AtPlayerGroggyFailPetternStorage = m_PattenManager->AtPlayerGroggyEnemyStorage;
	if (nowNode.size() < 1) return; // 플레이어가 입력을 안하면  return
	float countDamagePercent = 0.0f;
	// 적 연격이 끝났다는 델리게이트


	// 적이 플레이어에게 주는 데미지 계산
	countDamagePercent = m_PattenManager->CountDamageAtPlayerGroggy(nowNode);
	onEnemyFinalBlow.Invoke(m_PattenManager->AtPlayerGroggyFailPetternStorage); //CountDamageAtPlayerGroggy에서 담긴 값 반환해줌

	m_Player->GetDamageAtGroggy( m_Enemy->GetAttack() * EnemyAtkMulAtPlayerGroggy * (1 - countDamagePercent));

	m_PattenManager->AtPlayerGroggyFailPetternStorage; // 플레이어 패턴 받을 준비
	m_Player->SetState("Player_Hit");						// 플레이어 상태 변경 -> 공격 실패
	m_Enemy->SetState("Enemy_AttackSuccess");				// 적 상태 변경 -> 적 공격
	m_Enemy->IsOtherEndGroggy = false;		// 적 그로기 상태 해제
	m_Player->RestoreGroggy();
	//m_Enemy->IsOtherEndGroggy = true;  // 끝났다고 알림
	//m_Enemy->OtherGroggyTime = 0.0f;
	EndPlayerGroggyCleanup(false);
	nowNode.clear();
	m_PattenManager->AtPlayerGroggyFailPetternStorage.clear();
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
		allDistancePercent = m_PattenManager->NodePatternDistance(nowNode, false); // 연격 길이 퍼센트 반환
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
				Vector2 PlayerPerryP = { RandomHitPos_x(GuardPlayer), RandomHitPos_y(GuardPlayer) };
				m_Player->CallGuardEffect(0, PlayerPerryP);

				//방어 사운드
				auto SoundCom = owner->GetQuery()->FindByName("SOUNDSTAGE");
				IndexNum = static_cast<int>(RandomSound());
				switch(IndexNum)
				{
				case 0:
					if (SoundCom) {
						SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Dodge01");
						SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
					}
					break;
				case 1:
					if (SoundCom) {
						SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Dodge02");
						SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
					}
					break;
				}

				onPlayerDodge.Invoke(pair.second->NodePatten); // 회피성공을 외부에 알림[1/2]			
			}
			else // 회피 실패 
			{
				m_Player->SetState("Player_Hit");   			// 플레이어 상태 변경 -> 플레이어 피격
				m_Player->GetDamage( m_Enemy->GetAttack()); // 상중하 적용한 데미지

				if (HitAnimeCount2 < 9)
				{
					Vector2 randomP = { RandomHitPos_x(HiteffectPlayer), RandomHitPos_y(HiteffectPlayer) };
					float RandomRotate = RandomHitPos_Angle();
					m_Player->CallPlayerHit(HitAnimeCount2, randomP, RandomRotate);
					++HitAnimeCount2;
				}
				if (HitAnimeCount2 = 10) HitAnimeCount2 = 0;

				//피격 사운드
				auto SoundCom = owner->GetQuery()->FindByName("SOUNDSTAGE");
				if (SoundCom) {
					SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Hit01");
					SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
				}

				onPlayerHit.Invoke(pair.second->NodePatten); // 플레이어 피격을 외부에 알림[1/2]
			}

			// 기세 계산

			if (m_Player->GetIsGroggy()) {
				m_Player->GetDamage((pair.second->lastPosition, m_Enemy->GetSpiritAttack()));		// 플레이어는 데미지 받음
			}
			else {
				m_Enemy->RestoreSpiritDamage(m_Enemy->GetSpiritAttack());	// 적은기세를 회복
				m_Player->GetSpiritdamage( m_Enemy->GetSpiritAttack());		// 플레이어는 기세를 잃음
			}


		}
		m_PattenManager->SubPattern(pair.second->PattenID, "Time"); // 시간 종료된 패턴 제거
	}

	if (nowNode.size() < 1) return; // 플레이어가 입력한 노드가 없으면 무시

	//pattern* tmpCorPatten = m_PattenManager->CorrectPattern(nowNode); // 현재 들어온 노드 index들
	pattern* DefCorPatten = m_PattenManager->CheckDefencePattern(nowNode); // 현재 들어온 노드랑 적 공격이랑 패턴이 맞았는지
	pattern* AtkCorPatten = m_PattenManager->CheckAttackPattern(nowNode); // 현재 들어온 노드랑 플레이어의 공격이 알맞는지

	if (DefCorPatten != nullptr) {
		//방어 성공 처리
		m_Enemy->SetState("Enemy_AttackSuccess");				// 적 상태 변경 -> 적 공격 성공
		if ((DefCorPatten->PlayingAttackTime) <= 0.7f)			// 플레이어가 0.5초 이내에 가드시 -> 패링
		{
			std::vector<int> tmp = DefCorPatten->NodePatten;	// 플레이어 입력한 노드
			tmp.erase(std::remove(tmp.begin(), tmp.end(), 0), tmp.end());

			onParry.Invoke(tmp.back());		// 패링 이벤트 델리게이트 호출

			m_Player->SetState("Player_Perry"); // 플레이어 상태 변경 -> 플레이어 패링 상태


			std::vector<Vector2> PlayerPerry = { { RandomHitPos_x(PerryRect01), RandomHitPos_y(PerryRect01) } ,
				{ RandomHitPos_x(PerryRect02), RandomHitPos_y(PerryRect02) },
			{ RandomHitPos_x(PerryRect03), RandomHitPos_y(PerryRect03) } };
			m_Player->CallPerryEffect(PlayerPerry);

			//패리사운드
			IndexNum = static_cast<int>(RandomSound2());
			auto SoundCom = owner->GetQuery()->FindByName("SOUNDSTAGE");
			switch (IndexNum)
			{
			case 0:
				if (SoundCom) {
					SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Parry01");
					SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
				}
				break;
			case 1:
				if (SoundCom) {
					SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Parry02");
					SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
				}
				break;
			case 2:
				if (SoundCom) {
					SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Parry03");
					SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
				}
				break;
			}

			// 패링에 따른 기세값 반영
			if (!m_Player->GetIsGroggy()) {
				m_Player->RestoreSpiritDamage(ConvertSpiritDamageToPos(DefCorPatten->lastPosition, m_Enemy->GetSpiritAttack()));
				m_Enemy->GetSpiritdamage(ConvertSpiritDamageToPos(DefCorPatten->lastPosition, m_Enemy->GetSpiritAttack()));
			}
		}
		else // 플레이어 패링 실패
		{
			std::vector<int> tmp = DefCorPatten->NodePatten;
			tmp.erase(std::remove(tmp.begin(), tmp.end(), 0), tmp.end());
			onGuard.Invoke(tmp.back());

			m_Player->SetState("Player_Guard");		// 플레이어 상태 변경 -> 플레이어 방어

			//가드사운드
			IndexNum = static_cast<int>(RandomSound());
			auto SoundCom = owner->GetQuery()->FindByName("SOUNDSTAGE");
			switch (IndexNum)
			{
			case 0:
				if (SoundCom) {
					SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Guard01");
					SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
				}
				break;
			case 1:
				if (SoundCom) {
					SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Guard02");
					SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
				}
				break;
			}

			Vector2 PlayerPerryP = { RandomHitPos_x(GuardPlayer), RandomHitPos_y(GuardPlayer) };
			m_Player->CallGuardEffect(0, PlayerPerryP);


			// 패링 실패에 따른 기세값 변경
			if (m_Player->GetIsGroggy()) {
				m_Player->GetDamage(ConvertSpiritDamageToPos(DefCorPatten->lastPosition, m_Enemy->GetSpiritAttack()));
			}
			else {
				m_Enemy->RestoreSpiritDamage( m_Enemy->GetSpiritAttack());
				m_Player->GetSpiritdamage( m_Enemy->GetSpiritAttack());
			}

		}


		m_PattenManager->SubPattern(DefCorPatten->PattenID, "Enemy"); // 적 패턴 제거

	}
	else if (DefCorPatten == nullptr && AtkCorPatten != nullptr) {
				
		//공격 성공
		m_Player->SetState("Player_AttackSuccess");	// 플레이어 상태 변경 -> 플레이어 공격 성공
		m_Player->SetEndAttack();					// isAttackingPattern = true 
		//공격성공사운드
		IndexNum = static_cast<int>(RandomSound2());
		auto SoundCom = owner->GetQuery()->FindByName("SOUNDSTAGE");
		switch (IndexNum)
		{
		case 0:
			if (SoundCom) {
				SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Attack01");
				SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
			}
			break;
		case 1:
			if (SoundCom) {
				SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Attack02");
				SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
			}
			break;
		case 2:
			if (SoundCom) {
				SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Attack03");
				SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
			}
			break;
		}

		bool isHit = false;

		// 마지막 노드가 중앙이 아니라면 적이 일정 확률로 회피 
		if (m_Enemy->GetDefenseRate() >= GameRandom::RandomRange(1, 101) && AtkCorPatten->lastPosition != MiddleNode)
		{
			////////////////////////// 적의 방어 //////////////////////
			m_Enemy->SetState("Enemy_Defence");	// 적 상태 변경 -> 적 회피
			Vector2 EnemyPerryEff = { RandomHitPos_x(HiteffectEnemy), RandomHitPos_y(HiteffectEnemy) };
			m_Player->CallGuardEffect(0, EnemyPerryEff);

		
			isHit = false; // 가드
		}
		else // 적 회피 실패
		{

			////////////////////////// 적 피격 //////////////////
			m_Enemy->SetState("Enemy_Hit");		// 적 상태 변경 -> 적 피격
			float tmpDamage = m_PattenManager->NodePatternDistance(nowNode, true);
			m_Enemy->GetDamage(ConvertHPDamageToPos(AtkCorPatten->lastPosition, m_Player->GetAttack() * tmpDamage)); // 적 체력 감소

			if (HitAnimeCount < 9)
			{
				Vector2 randomP = { RandomHitPos_x(HiteffectEnemy), RandomHitPos_y(HiteffectEnemy) };
				float RandomRotate = RandomHitPos_Angle();
				m_Enemy->CallPlayerHit(HitAnimeCount, randomP, RandomRotate);
				++HitAnimeCount;
			}
			if (HitAnimeCount = 10) HitAnimeCount = 0;

			isHit = true; // 쳐맞음
		}

		onEnemyHit.Invoke(nowNode, isHit); // 외부에 피격발생 알림

		// 플레이어 공격에 따른 기세 값 변경
		m_Player->RestoreSpiritDamage(ConvertSpiritDamageToPos(AtkCorPatten->lastPosition, m_Player->GetSpiritAttack()));
		m_Enemy->GetSpiritdamage(ConvertSpiritDamageToPos(AtkCorPatten->lastPosition, m_Player->GetSpiritAttack()));

		m_PattenManager->PlayerPatternAllClear(); // 저장소에 패턴이 삭제가 안되는 경우도 있음으로 그냥 전부 삭제!!!

		m_PattenManager->SetDefenceIsfailControl(false); //공격 성공했음으로 실패처리를 안함!!

	}

	else if (DefCorPatten == nullptr && AtkCorPatten == nullptr) {
		//실패 처리
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
					////////////////////////// 아군의 방어 //////////////////
					//방어 사운드
					auto SoundCom = owner->GetQuery()->FindByName("SOUNDSTAGE");
					IndexNum = static_cast<int>(RandomSound());
					switch (IndexNum)
					{
					case 0:
						if (SoundCom) {
							SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Dodge01");
							SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
						}
						break;
					case 1:
						if (SoundCom) {
							SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Dodge02");
							SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
						}
						break;
					}

					Vector2 PlayerPerryP = { RandomHitPos_x(GuardPlayer), RandomHitPos_y(GuardPlayer) };
					m_Player->CallGuardEffect(0, PlayerPerryP);

					onPlayerDodge.Invoke(tmpPatten->NodePatten); // 회피성공을 외부에 알림[2/2]
				}
				else
				{
					m_Player->SetState("Player_Hit");   			// 플레이어 상태 변경 -> 플레이어 피격됨 
					m_Player->GetDamage(ConvertHPDamageToPos(tmpPatten->lastPosition, m_Enemy->GetAttack()));
					//피격사운드
					auto SoundCom = owner->GetQuery()->FindByName("SOUNDSTAGE");
					if (SoundCom) {
						SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Hit01");
						SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
					}

					onPlayerHit.Invoke(tmpPatten->NodePatten); // 플레이어 피격을 외부에 알림[2/2]

					if (HitAnimeCount2 < 9)
					{
						Vector2 randomP = { RandomHitPos_x(HiteffectPlayer), RandomHitPos_y(HiteffectPlayer) };
						float RandomRotate = RandomHitPos_Angle();
						m_Player->CallPlayerHit(HitAnimeCount2, randomP, RandomRotate);
						++HitAnimeCount2;
					}
					if (HitAnimeCount2 = 10) HitAnimeCount2 = 0;
				}

				// 기세 계산		Object_SpiritAttack	7.00000000	float

				if (!m_Player->GetIsGroggy()) {
					m_Player->GetSpiritdamage(ConvertSpiritDamageToPos(tmpPatten->lastPosition, m_Player->GetSpiritAttack()));
					m_Enemy->RestoreSpiritDamage(ConvertSpiritDamageToPos(tmpPatten->lastPosition, m_Player->GetSpiritAttack()));
				}


				// 사용된 적 패턴 제거
				m_PattenManager->SubPattern(tmpPatten->PattenID, "Enemy");
			}
			else // 플레이어 가이드 라인에 관한 실패
			{
				m_Player->SetState("Player_AttackFail");	// 플레이어 상태 변경 -> 플레이어 공격 실패
				m_Player->SetEndAttack();					// isAttackingPattern = true -> ??

				// 플레이어 가이드 패턴 파괴
				
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
		m_Player->enemyGroggyTime = 0.0f;

	}

	m_Player->OtherGroggyTimeStop = isPlayingAni;
	// 타임아웃 신호 수신 시 적 그로기 종료 처리
	if (m_Player->isOtherGroggyEnd) {
		m_Player->isOtherGroggyEnd = false;

		onTimeout.Invoke(); //    //  외부 알림

		EndEnemyGroggyCleanup(true);
	}
}


void BettleManager::SetAnimationAtOtherGroggy() {
	if (tmpAttackNode.size() < 2) {
		isPlayingAni = false;
		return;
	}
		

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
			int randindex = stepIdx % 4;
			m_Player->AttackAniSelect(randindex); // 필요하면 다른 매핑으로 변경


			// 0 : 좌우,   1 : 상하,  2. 좌상 ,  3. 가드 : 우상
			switch (randindex) {
			case 0:
			{
				auto camIns = owner->GetQuery()->FindByName("CAM");
				if (camIns) { camIns->GetComponent<CamInstance>()->Start(1.0f, 10.0f, 10.0f, ShakeType::X);
				camIns->GetComponent<CamInstance>()->SetFastToSlow();
				}
				break;
			}
			case 1:
			{
				auto camIns = owner->GetQuery()->FindByName("CAM");
				if (camIns) { camIns->GetComponent<CamInstance>()->Start(1.0f, 10.0f, 10.0f, ShakeType::Y);
				camIns->GetComponent<CamInstance>()->SetFastToSlow();
				}
				break;
			}
			case 2:
			{
				auto camIns = owner->GetQuery()->FindByName("CAM");
				if (camIns) { camIns->GetComponent<CamInstance>()->Start(1.0f, 10.0f, 10.0f, ShakeType::XY);
				camIns->GetComponent<CamInstance>()->SetFastToSlow();
				}
				break;
			}
			case 3:
			{
				auto camIns = owner->GetQuery()->FindByName("CAM");
				if (camIns) { camIns->GetComponent<CamInstance>()->Start(1.0f, 10.0f, 10.0f, ShakeType::X_Y);
				camIns->GetComponent<CamInstance>()->SetFastToSlow();
				}
				break;
			}
			}

			//연격사운드
			auto SoundCom = owner->GetQuery()->FindByName("SOUNDSTAGE");
			IndexNum = static_cast<int>(RandomSound2());
			switch (IndexNum)
			{
			case 0:
				if (SoundCom) {
					SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Attack01");
					SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
				}
				break;
			case 1:
				if (SoundCom) {
					SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Attack02");
					SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
				}
				break;
			case 2:
				if (SoundCom) {
					SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Attack03");
					SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
				}
				break;
			}

		}
	}
	else {
		// 재생 종료 및 리셋
		isPlayingAni = false;
		m_Player->AttackAniSelect(4);
		AniTime = 0.0f;
		stepIdx = -1;
		tmpAttackNode.clear();
	}

}


void BettleManager::ChangeFinalStatePlayerGroggy() // 아군의  그로기 상태에서 적과 플레이어의 상태를 변하게 하는 함수 
{

	if (!m_Enemy->IsOtherGroggy) {
		m_Enemy->IsOtherGroggy = true;
		m_Enemy->OtherGroggyTime = 0.0f;
		
	}

	if (isPlayingAni)  m_Player->OtherGroggyTimeStop = true;
	else               m_Player->OtherGroggyTimeStop = false;

	if (m_Enemy->IsOtherEndGroggy) {		
		m_Enemy->IsOtherEndGroggy = false;

		m_Enemy->IsOtherGroggy = false;
		m_Player->GetDamageAtGroggy(m_Enemy->GetAttack() * 1.0f * EnemyAtkMulAtPlayerGroggy);
		
		onEnemyFinalBlow.Invoke(m_PattenManager->AtPlayerGroggyFailPetternStorage);
    
		m_Player->SetState("Player_Hit");
		m_Enemy->SetState("Enemy_AttackSuccess"); 
		auto SoundCom = owner->GetQuery()->FindByName("SOUNDSTAGE");
		if (SoundCom) {
			SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Hit01");
			SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
		}
		m_Player->RestoreGroggy();
		EndPlayerGroggyCleanup(true);
		m_PattenManager->AtPlayerGroggyFailPetternStorage.clear();
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
	if (m_Enemy->GetIsGroggy()) { // 적 그로기인경우
		if (!isEffectOnce) {
			//연출 << 반짝 넣어주면 됨
			giseObj->BlinkBlack();
			isEffectOnce = true;
			//그로기 사운드
			auto SoundCom = owner->GetQuery()->FindByName("SOUNDSTAGE");
			if (SoundCom) {
				SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Break01");
				SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
			}
		}
		giseObj->SetMaxGague(20.0f);
		//std::cout << m_Player->enemyGroggyTime << "끼얏끼얏호우!!!!" << std::endl; // 왜인지 모르지만 20초임, 오른쪽에서 왼쪽, 즉 1 -> 0이 되야함
		giseChangeValue = 20.0f - m_Player->enemyGroggyTime; // 1 ~ 0
		giseObj->CalculateValue(giseChangeValue);

	}
	else if (m_Player->GetIsGroggy()) { //플레이어 그로기인 경우
		if (!isEffectOnce) {
			//연출 << 반짝 넣어주면 됨
			giseObj->BlinkWhite();
			//그로기 사운드
			auto SoundCom = owner->GetQuery()->FindByName("SOUNDSTAGE");
			if (SoundCom) {
				SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Break01");
				SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
			}
			isEffectOnce = true;
		}
		giseObj->SetMaxGague(10.0f);
		// 플레이어의 그로기타임
		//std::cout << m_Enemy->OtherGroggyTime << "끼뺫끼뺫!!!!" << std::endl; // 왜인진 모르지만 10초임 + 왼쪽에서 오른쪽, 즉 0 -> 1이 되야함
		giseChangeValue = m_Enemy->OtherGroggyTime; // 0 ~ 1
		giseObj->CalculateValue(giseChangeValue);
	}
	else { // 둘다 그로기가 아닌경우
		isEffectOnce = false;
		giseObj->SetMaxGague(giseTotalValue);
		giseChangeValue = m_Player->GetNowSpiritAmount();
		giseObj->CalculateValue(giseChangeValue);
	}
}

/// 아군 홀드 공격 완료!!!
void BettleManager::FinalAttackToEnemy() // 델리게이트로 외부에서 연결	
{
	// 적이 그로기 상태일 때
	if (m_Enemy->GetIsGroggy())
	{
		m_Enemy->GetDamage((m_Player->GetAttack() * allDistancePercent * 20.0f) + 100.0f);  /// 나중에 적 hp 배율 따로 빼기!!!!
		m_Enemy->SetState("Enemy_Hit");				// 적 상태 변경 -> 적 피격
		if (HitAnimeCount < 9)
		{
			Vector2 randomP = { RandomHitPos_x(HiteffectEnemy), RandomHitPos_y(HiteffectEnemy) };
			float RandomRotate = RandomHitPos_Angle();
			m_Enemy->CallPlayerHit(HitAnimeCount, randomP, RandomRotate);
			++HitAnimeCount;
		}
		if (HitAnimeCount = 10) HitAnimeCount = 0;

		m_Player->isOtherGroggyEnd = false;		// 적 그로기 상태 해제
		m_Player->SetState("Player_AttackSuccess");	// 플레이어 상태 변경 -> 공격 성공
		EndEnemyGroggyCleanup(false);
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

	//적 그로기로 진입하는 첫 프레임 , 플레이어가 재는 타이머를 0으로
	if (preManagerState != nowManagerState && nowManagerState == enemyGroggy) {
		m_Player->IsOtherGroggy = true;          // 표시도 함께 세팅
		m_Player->enemyGroggyTime = 0.0f;        // 반드시 0부터 시작
		
	}
	
	 //플레이어 그로기로  진입하는 첫 프레임, 적이 재는 타이머를 0으로
	if (preManagerState != nowManagerState && nowManagerState == playerGroggy) {
		m_Enemy->IsOtherGroggy = true;           // 표시도 함께 세팅
		m_Enemy->OtherGroggyTime = 0.0f;         // 반드시 0부터 시작
	}

	// 상태에 변경이 있고 이전 상태가 적 그로기 상태면 
	if (preManagerState != nowManagerState && preManagerState == enemyGroggy)
	{
		allDistancePercent = 0.0f;
		isOncePatternAttack = false;
		m_Player->isOtherGroggyEnd = false;
		m_Player->IsOtherGroggy = false;
		m_Player->SetState("Player_AttackSuccess");
		m_Enemy->SetState("Enemy_Hit");

		onTimeout.Invoke(); // 외부에 그로기 지속 시간이 끝났다는걸 알림
		EndEnemyGroggyCleanup(true);
	}

	if (preManagerState != nowManagerState && preManagerState == playerGroggy)
	{
		isOncePatternAttack = false;
		m_Player->isOtherGroggyEnd = false;
		m_Player->IsOtherGroggy = false;
	}




	preManagerState = nowManagerState;

	//if (preManagerState != nowManagerState && nowManagerState == playerGroggy)
	//{
	//	auto SoundCom = owner->GetQuery()->FindByName("SOUNDSTAGE");
	//	if (SoundCom) {
	//		SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"Break01");
	//		SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
	//	}
	//}
}

void BettleManager::ResetState()
{

}


void BettleManager::EndEnemyGroggyCleanup(bool byTimeout)
{
	//BettleManager 값 정리
	allDistancePercent = 0.0f;
	isOncePatternAttack = false;
	isPlayingAni = false;
	AniTime = 0.0f;
	//usedStartBlow = false;
	tmpAttackNode.clear();

	//플레이어 측 표시/타이머 정리
	m_Player->IsOtherGroggy = false;
	m_Player->isOtherGroggyEnd = false;
	m_Player->OtherGroggyTimeStop = false;
	m_Player->enemyGroggyTime = 0.0f;  // 플레이어가 잰 "적 그로기 타이머"

	//적 측 표시/타이머 정리
	m_Enemy->IsOtherGroggy = false;     // 혹시 남아있을 수 있는 표시는 끔
	m_Enemy->IsOtherEndGroggy = false;


	// 타임아웃인 경우엔 공통 회복 루틴 태우기(둘 다 절반으로)
	if (byTimeout) {
		m_Enemy->SetIsRestore(true);
		m_Player->SetIsRestore(true);
	}

	// 다음 패턴이 다시 나오도록 트리거 (안전빵)
	m_Player->SetEndAttack();
}

void BettleManager::EndPlayerGroggyCleanup(bool byTimeout)
{
	//BettleManager 값 정리
	//usedStartBlow = false;

	//적 측 표시/타이머 정리
	m_Enemy->IsOtherGroggy = false;
	m_Enemy->IsOtherEndGroggy = false;
	m_Enemy->OtherGroggyTime = 0.0f;

	//플레이어 표시 정리 
	m_Player->IsOtherGroggy = false;   // 상대 그로기 표시용
	m_Player->isOtherGroggyEnd = false;

	

	// 타임아웃이면 공통 회복 루틴도 태우기
	if (byTimeout) {
		m_Enemy->SetIsRestore(true);
		m_Player->SetIsRestore(true);
	}

	// 플레이어 쪽 패턴 루프 재가동
	m_Player->SetEndAttack();
}
