#include "BettleManager.h"
#include <random>
#include <cmath>
#include "../LiveObject/Player.h"
#include "../LiveObject/Enemy.h"
#include "../LiveObject/LiveObject.h"
#include "AttackPatternManager.h"
#include "Components/Base/GameObject.h"
#include "Components/Base/MonoBehavior.h"
#include "Scripts/GameManager.h"





void BettleManager::OnStart() {
	//m_Enemy = owner->GetQuery()->FindByName("Enemytmp")->GetComponent<Enemy>();
	//m_Player = owner->GetQuery()->FindByName("Playertmp")->GetComponent<Player>();
	m_Player->SetSpiritData(m_Enemy->GetSpiritAmount());
	m_PattenManager = owner->GetQuery()->FindByName("AttackPattenManager")->GetComponent<AttackPatternManager>();

	preSpiritAmount = m_Player->GetNowSpiritAmount();

	owner->AddComponent<GiseGauge>();
	giseObj = owner->GetComponent<GiseGauge>();

	TotalValue = m_Player->GetSpiritAmount();
	/*giseObj->SetMaxGague(TotalValue);*/



	//HpObj = owner->AddComponent<HpGauge>();
	////HP 최대치 설정 플레이어, 적
	//HpObj->SetPlayerMaxGague(m_Player->GetTotalHp());
	//HpObj->SetEnemyMaxGague(m_Enemy->GetTotalHp());



	/*HpObj->SetHpUiPosition(Player, Enemy);*/

	int a = 0;
}

void BettleManager::OnUpdate() {
	SetGroggyState();
	//HpObj->SetHpUiPosition(Player2, Enemy2);

	// 게임 상태가 Pause면 모든 Update 내용 무시
	if (Singleton<GameManager>::GetInstance().GetGameState() == GameState::Pause)
	{
		return;
	}

	SetStateFormPattern();	// 각 상태별 공격 방어 처리 어
	ChangeFinalState();		// 각 LiveObject의 사망 처리 Update - 유니티의 AnyState 유사
	SetSpiritGauge();		// 기세 게이지 업데이트
	//
	/*HpObj->CalculatePlayerValue(m_Player->GetHp());
	HpObj->CalculateEnemyValue(m_Enemy->GetHp());*/

	//
	ResetState(); 			// state가 다를 경우 초기화 하기!!!
}

// -> 생성자로 넣어야 할듯?
void BettleManager::SetForStart(AttackPatternManager* pattenManager) {
	m_PattenManager = pattenManager;
}


// 하드코딩용 : 입력 패턴 고정



// 노드 인풋 
void BettleManager::SetInputNode(std::vector<int> InputNode) {
	nowNode = InputNode;
}

//들어온 입력 노드에 따라서 공격, 방어를 처리하는 함수
void BettleManager::SetStateFormPattern() {

	if (!m_Player->GetIsGroggy() && !m_Enemy->GetIsGroggy()) { // 그로기가 아니면!!
		nowManagerState = noneGroggy;
		std::unordered_map<std::string, pattern*> tmpTimePatten = m_PattenManager->TimeOutPatten();  // 패턴이 공격 시간이 지났다면 
		for (const auto& pair : tmpTimePatten) {
			if (pair.second->PattenID.substr(0, 2) == "EP")            //적 패턴일시
			{
				m_Enemy->SetState("Enemy_AttackSuccess");			 // 적 공격 성공
				if (m_Player->GetDefenseRate() >= RandomReturn(100) && pair.second->lastPosition != MiddleNode) {
					m_Player->SetState("Player_Defence");			 // 방어
				}
				else {
					m_Player->SetState("Player_Hit");   			// 피격됨
					m_Player->GetDamage(
						ConvertHPDamageToPos(pair.second->lastPosition, m_Enemy->GetAttack())); // 상중하 적용한 데미지
				}
				// 기세 계산
				m_Enemy->RestoreSpiritDamage(
					ConvertSpiritDamageToPos(pair.second->lastPosition, m_Enemy->GetSpiritAttack())); // 적은기세를 회복
				m_Player->GetSpiritdamage(
					ConvertSpiritDamageToPos(pair.second->lastPosition, m_Enemy->GetSpiritAttack()));  // 플레이어는 기세를 잃음
			}
			m_PattenManager->SubPattern(pair.second->PattenID, "Time");
		}

		if (nowNode.size() < 1) return;

		pattern* tmpCorPatten = m_PattenManager->CorrectPattern(nowNode);
		// 입력이 적, 플레이어의 패턴과 맞을 경우
		if (tmpCorPatten != nullptr) {
			if (tmpCorPatten->PattenID.substr(0, 2) == "EP") {
				m_Enemy->SetState("Enemy_AttackSuccess");
				if ((tmpCorPatten->PlayingAttackTime) <= 0.5f) {  // 플레이어가 0.5초 이내에 가드시 -> 패링
					std::vector<int> tmp = tmpCorPatten->NodePatten;
					tmp.erase(std::remove(tmp.begin(), tmp.end(), 0), tmp.end());

					onParry.Invoke(tmp.front());

					m_Player->SetState("Player_Perry");
					m_Player->RestoreSpiritDamage(
						ConvertSpiritDamageToPos(tmpCorPatten->lastPosition, m_Enemy->GetSpiritAttack()));  // 기세 변경
					m_Enemy->GetSpiritdamage(
						ConvertSpiritDamageToPos(tmpCorPatten->lastPosition, m_Enemy->GetSpiritAttack()));

				}
				else {
					std::vector<int> tmp = tmpCorPatten->NodePatten;
					tmp.erase(std::remove(tmp.begin(), tmp.end(), 0), tmp.end());
					onGuard.Invoke(tmp.front());

					m_Player->SetState("Player_Guard");		// 가드
					m_Enemy->RestoreSpiritDamage(
						ConvertSpiritDamageToPos(tmpCorPatten->lastPosition, m_Enemy->GetSpiritAttack()));  // 기세 변경
					m_Player->GetSpiritdamage(
						ConvertSpiritDamageToPos(tmpCorPatten->lastPosition, m_Enemy->GetSpiritAttack()));
				}
				m_PattenManager->SubPattern(tmpCorPatten->PattenID, "Enemy");
			}
			else {
				m_Player->SetState("Player_AttackSuccess");   // 플레이어의 공격 성공
				m_Player->SetEndAttack();
				if (m_Enemy->GetDefenseRate() >= RandomReturn(100) && tmpCorPatten->lastPosition != MiddleNode)
					m_Enemy->SetState("Enemy_Defence"); // 방어

				else {
					m_Enemy->SetState("Enemy_Hit"); // 피격됨`
					m_Enemy->GetDamage(
						ConvertHPDamageToPos(tmpCorPatten->lastPosition, m_Player->GetAttack()));
				}
				m_Player->RestoreSpiritDamage(
					ConvertSpiritDamageToPos(tmpCorPatten->lastPosition, m_Player->GetSpiritAttack()));
				m_Enemy->GetSpiritdamage(
					ConvertSpiritDamageToPos(tmpCorPatten->lastPosition, m_Player->GetSpiritAttack()));


				m_PattenManager->SearchAndDestroyCouple(tmpCorPatten->PattenID);
				m_PattenManager->SubPattern(tmpCorPatten->PattenID, "Player");
			}
		}


		// 입력이 기존 가이드라인, 적 공격과 다를경우
		else {
			pattern* tmpPatten = m_PattenManager->failPattern(nowNode);
			if (tmpPatten != nullptr) {   // 실패한 패턴이 있는 경우
				if (tmpPatten->PattenID.substr(0, 2) == "EP") {
					m_Enemy->SetState("Enemy_AttackSuccess");			 // 적 공격 성공

					if (m_Player->GetDefenseRate() >= RandomReturn(100)) {
						m_Player->SetState("Player_Defence");			 // 방어
					}
					else {
						m_Player->SetState("Player_Hit");   			// 피격됨
						m_Player->GetDamage(
							ConvertHPDamageToPos(tmpPatten->lastPosition, m_Enemy->GetAttack()));
					}
					m_Player->RestoreSpiritDamage(
						ConvertSpiritDamageToPos(tmpPatten->lastPosition, m_Player->GetSpiritAttack())); // 기세 계산
					m_Enemy->GetSpiritdamage(
						ConvertSpiritDamageToPos(tmpPatten->lastPosition, m_Player->GetSpiritAttack()));

					m_PattenManager->SubPattern(tmpPatten->PattenID, "Enemy");
				}
				else {
					m_Player->SetState("Player_AttackFail");
					m_Player->SetEndAttack();
					m_PattenManager->SearchAndDestroyCouple(tmpPatten->PattenID);
					m_PattenManager->SubPattern(tmpPatten->PattenID, "Player");
				}
			}
		}


	}
	//else if (m_Player->GetIsGroggy() && m_Enemy->GetIsGroggy()) {  // 적과 아군의 그로기가 동시에 걸린 경우 // 버그 터지면 처리해!!!!!

	//}
	else if (m_Enemy->GetIsGroggy()) { // 적이 그로기에 걸린 경우 
		m_PattenManager->EnemyPatternAllClear();  //이것도 잘 처리하기!!!
		m_PattenManager->PlayerPatternAllClear();
		m_PattenManager->DoneTimeOutPatten();



		if (nowNode.size() < 2) return; //플레이어가 입력을 하기 전까지 빠져나가질 못함 (8.12 확인)

		if (allDistancePercent <= 0.0f) {	   //퍼센트가 0 이라면 길이에 따라서 배율 넣기 , 문제 있을 수 있음
			onFinalBlow.Invoke(); // 외부에 공격 준비를 알림(총알이 장전된거임)
			allDistancePercent = m_PattenManager->OnceAllNodePatternDistance(nowNode);
		}
	}
	else if (m_Player->GetIsGroggy() ) { // 아군이 그로기에 걸린경우
		m_PattenManager->EnemyPatternAllClear();  //이것도 잘 처리하기!!!
		m_PattenManager->PlayerPatternAllClear();
		m_PattenManager->DoneTimeOutPatten();
		m_Player->GetDamage(m_Enemy->GetAttack() * 2.5f);
		m_Player->SetState("Player_Hit");
		m_Enemy->SetState("Enemy_AttackSuccess");
	}
	nowNode.clear();
}

//범위 안의 값을 랜덤하게 return
int  BettleManager::RandomReturn(int MaxInt) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, MaxInt); // 1 ~ 10 사이의 정수
	int randomValue = dist(gen);
	return randomValue;
}

// State정하기
//그로기 + 죽음
void BettleManager::ChangeFinalState() {
	if (m_Player->GetHp() <= 0.0f) {
		m_Player->SetState("Player_Dead");
	}
	if (m_Enemy->GetHp() <= 0.0f) {
		m_Enemy->SetState("Enemy_Dead");
	}

	if (m_Enemy->GetIsRestore() || m_Player->GetIsRestore()) // 적과 아군 둘중 그로기가 끝나고 회복해야한다면
	{
		m_Enemy->ResetSpiritAmount();  // 서로 기세게이지가 절반으로 돌아감
		m_Player->ResetSpiritAmount();
		m_Enemy->SetIsRestore(false);  // 기세 게이지 회복 표시
		m_Player->SetIsRestore(false);
	}
	else if ((!m_Player->GetIsGroggy()) && m_Player->GetNowSpiritAmount() <= 0.0f) {
		m_Player->SetState("Player_Groggy");
		m_Player->SetIsGroggy(true);
		m_Enemy->SetIsOtherEndGroggy(true);
		m_Enemy->isFirstSpiriteDown = true;  // 오류 수정하기!!
	}
	else if ((!m_Enemy->GetIsGroggy()) && m_Enemy->GetNowSpiritAmount() <= 0.0f) {
		m_Enemy->SetState("Enemy_Groggy");
		m_Enemy->SetIsGroggy(true);
		m_Player->SetIsOtherEndGroggy(true);
		isOncePatternatk = true;
	}
	






	if (m_Enemy->GetIsGroggy() && !m_Player->GetIsOtherEndGroggy()) {
		onTimeout.Invoke();
		m_Enemy->RestoreGroggy();
	}
	else if (m_Player->GetIsGroggy() && !m_Enemy->GetIsOtherEndGroggy()) {
		m_Player->RestoreGroggy();
	}

}

void BettleManager::SetSpiritGauge() {
	giseObj->SetMaxGague(TotalValue);
	ChangeValue = m_Player->GetNowSpiritAmount();
	/*preSpiritAmount = m_Player->GetNowSpiritAmount();*/
	giseObj->CalculateValue(ChangeValue);
}

/// 아군 홀드 공격 완료!!!
void BettleManager::FinalAttackToEnemy() { // 델리게이트로 외부에서 연결
	if (m_Enemy->GetIsGroggy()) {
		m_Enemy->GetDamage((m_Player->GetAttack() * allDistancePercent * 10.0f));  /// 나중에 적 hp 배율 따로 빼기!!!!
		m_Enemy->SetState("Enemy_Hit");
		m_Player->SetIsOtherEndGroggy(false);
		m_Player->SetState("Player_AttackSuccess");
	}
	// 적과 아군 state 끝

}



//
void BettleManager::SetGroggyState() {
	preManagerState = nowManagerState;
	if (m_Player->GetIsGroggy()) {
		nowManagerState = playerGroggy;
	}
	else if (m_Enemy->GetIsGroggy()) {
		nowManagerState = enemyGroggy;
	}
	else if ((!m_Enemy->GetIsGroggy()) && (!m_Player->GetIsGroggy())) {
		nowManagerState = noneGroggy;
	}
	else {
		nowManagerState = noneGroggy;
	}
}


void BettleManager::ResetState() {
	if (preManagerState != nowManagerState && preManagerState == enemyGroggy) {
		allDistancePercent = 0.0f;
		isOncePatternatk = false;
		onTimeout.Invoke(); // 외부에 그로기 지속 시간이 끝났다는걸 알림 << 이거, 성공했을때는 잡히는데 실패할때 안잡히네
	}
}