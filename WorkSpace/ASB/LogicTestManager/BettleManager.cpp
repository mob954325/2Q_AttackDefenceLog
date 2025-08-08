#include "BettleManager.h"
#include <random>
#include <cmath>
#include "../LiveObject/Player.h"
#include "../LiveObject/Enemy.h"
#include "../LiveObject/LiveObject.h"
#include "AttackPatternManager.h"
#include "Components/Base/GameObject.h"
#include "Components/Base/MonoBehavior.h"


void BettleManager::OnStart() {
	//m_Enemy = owner->GetQuery()->FindByName("Enemytmp")->GetComponent<Enemy>();
	//m_Player = owner->GetQuery()->FindByName("Playertmp")->GetComponent<Player>();
	m_Player->SetSpiritData(m_Enemy->GetSpiritAmount());
	m_PattenManager = owner->GetQuery()->FindByName("AttackPattenManager")->GetComponent<AttackPatternManager>();
	PrecticeNode();
}

void BettleManager::OnUpdate() {
	SetStateFormPattern();
	ChangeFinalState();
}

// -> 생성자로 넣어야 할듯?
void BettleManager::SetForStart(AttackPatternManager* pattenManager) {
	m_PattenManager = pattenManager;
}


// 하드코딩용 : 입력 패턴 고정
void BettleManager::PrecticeNode() {
	nowNode.push_back(5);
	nowNode.push_back(1);
	nowNode.push_back(7);
}


// 노드 인풋 
void BettleManager::SetInputNode(std::vector<int> InputNode) {
	/*nowNode = InputNode;*/
}

void BettleManager::SetStateFormPattern(){		  //현재 마우스의 입력 받기  -> 승규님 데이터 받기
	while(1) {
		pattern* tmpPatten = m_PattenManager->TimeOutPatten();  // 패턴이 공격 시간이 지났다면 

		if (tmpPatten == nullptr) break;

		if (tmpPatten->PattenID.substr(0, 2) == "EP")            //적 패턴일시
		{
			m_Enemy->SetState("Enemy_AttackSuccess");			 // 적 공격 성공
			if (m_Player->GetDefenseRate() >= RandomReturn(100)) {
				m_Player->SetState("Player_Defence");			 // 방어
			}
			else {
				m_Player->SetState("Player_Hit");   			// 피격됨
				m_Player->GetDamage(m_Enemy->GetAttack());
			}
			m_Enemy->RestoreSpiritDamage(m_Enemy->GetSpiritAttack()); // 기세를 회복
			m_Player->GetSpiritdamage(m_Enemy->GetSpiritAttack());    // 플레이어는 기세를 잃음
		}
		
		m_PattenManager->SubPattern(tmpPatten->PattenID, true);
	}


	if (nowNode.size() < 2) return;

		// 입력이 적, 플레이어의 패턴과 맞을 경우
	while (1) {
		pattern* tmpPatten = m_PattenManager->CorrectPattern(nowNode);
		if (tmpPatten == nullptr) break;
		if (tmpPatten->PattenID.substr(0, 2) == "EP") {
			if ((tmpPatten->TotalPlayingAttackTime - tmpPatten->PlayingAttackTime) <= 0.5 ){  // 플레이어가 0.5초 이내에 가드시 -> 패링
				m_Player->SetState("Player_Perry");
			}
			else {
				m_Player->SetState("Player_Guard");		// 가드
				m_Enemy->RestoreSpiritDamage(m_Enemy->GetSpiritAttack());  // 기세 변경
				m_Player->GetSpiritdamage(m_Enemy->GetSpiritAttack());
			}
		}
		else {
			m_Player->SetState("Player_AttackSuccess");   // 플레이어의 공격 성공
			m_Player->SetEndAttack();
			if (m_Enemy->GetDefenseRate() >= RandomReturn(100))
				m_Enemy->SetState("Enemy_Defence"); // 방어

			else {
				m_Enemy->SetState("Enemy_Hit"); // 피격됨
				m_Enemy->GetDamage(m_Player->GetAttack());
			}
			m_Player->RestoreSpiritDamage(m_Player->GetSpiritAttack());
			m_Enemy->GetSpiritdamage(m_Player->GetSpiritAttack());
			m_PattenManager->SearchAndDestroyCouple(tmpPatten->PattenID);
		}
		m_PattenManager->SubPattern(tmpPatten->PattenID, false);
	}
		
		
	
	   // 플레이어가 공격이나 방어에 실패한 경우
	while (1) {
		pattern* tmpPatten = m_PattenManager->failPattern(nowNode);
		if (tmpPatten == nullptr) break;   // 실패한 패턴이 없을 경우

		if (tmpPatten->PattenID.substr(0, 2) == "EP") {
			m_Enemy->SetState("Enemy_AttackSuccess");			 // 적 공격 성공
			if (m_Player->GetDefenseRate() >= RandomReturn(100)) {
				m_Player->SetState("Player_Defence");			 // 방어
			}
			else {
				m_Player->SetState("Player_Hit");   			// 피격됨
				m_Player->GetDamage(m_Enemy->GetAttack());
			}
			m_Player->RestoreSpiritDamage(m_Player->GetSpiritAttack()); // 기세 계산
			m_Enemy->GetSpiritdamage(m_Player->GetSpiritAttack());
		}
		else {
			m_Player->SetState("Player_AttackFail");
			m_Player->SetEndAttack();
			m_PattenManager->SearchAndDestroyCouple(tmpPatten->PattenID);
		}
		m_PattenManager->SubPattern(tmpPatten->PattenID, false);
		
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
void BettleManager::ChangeFinalState() {
	if (m_Player->GetHp() <= 0.0f) {
		m_Player->SetState("Player_Dead");
	}
	if (m_Enemy->GetHp() <= 0.0f) {
		m_Enemy->SetState("Enemy_Dead");
	}
	if (!m_Player->GetIsGroggy() && m_Player->GetNowSpiritAmount() <= 0.0f) {
		m_Player->SetState("Player_Groggy");
		m_Player->SetIsGroggy(true);
	}
	if (!m_Enemy->GetIsGroggy() && m_Enemy->GetNowSpiritAmount() <= 0.0f) {
		m_Enemy->SetState("Enemy_Groggy");
		m_Enemy->SetIsGroggy(true);
	}
}


void BettleManager::DeciedBettelState(){ //마우스 데이터를 비교해서 현재 상태 결정하기

}



//상중하 판별 용도, 추가되면 가이드라인 추가에 넣어주기
enum AttackPosition { UpNode, MiddleNode, LowNode, NonePos };

AttackPosition ConvertEndNodeToPosition(int endNode, int Damage) {
	int tmpDanamge = 0;
	switch (endNode)
	{
	case 1:  return UpNode;
	case 2:  return UpNode;
	case 3:  return UpNode;
	case 4:  return MiddleNode;
	case 5:  return MiddleNode;
	case 6:  return MiddleNode;
	case 7:  return LowNode;
	case 8:  return LowNode;
	case 9:  return LowNode;
	default: return NonePos;
	}
}