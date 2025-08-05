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
}

void BettleManager::OnUpdate() {

}




// -> 생성자로 넣어야 할듯?
void BettleManager::SetForStart(AttackPatternManager& pattenManager) {
	m_PattenManager = pattenManager;
}


//Scene에서 deltaTime 설정 -> 임시 -> 없어도 됨!!
void BettleManager::SetDeltaTime(float deltaTime) { 
	m_DeltaTime = deltaTime; 

}



void BettleManager::ComparePatten( std::vector<int> InputNode){		  //현재 마우스의 입력 받기  -> 승규님 데이터 받기
	while(1) {
		pattern* tmpPatten = m_PattenManager.TimeOutPatten();
		if (tmpPatten == nullptr)
			break;
		if (tmpPatten->PattenID.substr(0, 2) == "EP") {
			m_Enemy->SetState("Enemy_AttackSuccess");   // 적 공격 성공
			if (m_Player->GetDefenseRate() >= RandomReturn(100)) {
				m_Player->SetState("Player_Defence"); // 방어
			}
			else {
				m_Player->SetState("Player_Hit");   	// 피격됨
			}
			m_Player->GetDamage(m_Enemy->GetAttack());
		}
		else {
			m_Player->SetState("Player_AttackFail");
		}
	}

	pattern* tmpPatten = m_PattenManager.CorrectPattern(InputNode);
		// 플레이어 , 적 상태 변경 + 공방계산
	if (tmpPatten == nullptr)
		return;
	if (tmpPatten->PattenID.substr(0, 2) == "EP") {
		m_Player->SetState("Player_Guard");			// 가드
		if (m_Enemy->GetAttackTimePercent() >= 75) {
			m_Enemy->SetState("Player_Perry");		//패링
		}
	}
	else {
		m_Player->SetState("Player_AttackSuccess");
		if (m_Enemy->GetDefenseRate() >= RandomReturn(100))
			m_Enemy->SetState("Enemy_Defence"); // 방어

		else {
			m_Enemy->SetState("Enemy_Hit"); // 피격됨
			m_Enemy->GetDamage(m_Player->GetAttack());
		}
		m_Enemy->GetSpiritdamage(m_Player->GetSpiritAttack());
	}
}

//범위 안의 값을 랜덤하게 return
int  BettleManager::RandomReturn(int MaxInt) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, MaxInt); // 1 ~ 10 사이의 정수
	int randomValue = dist(gen);
	return randomValue;
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