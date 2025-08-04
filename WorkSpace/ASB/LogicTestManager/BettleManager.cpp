#include "BettleManager.h"
#include <random>
#include <cmath>
#include "../LiveObject/Player.h"
#include "../LiveObject/Enemy.h"
#include "../LiveObject/LiveObject.h"






//void BettleManager::OnStart() {
//	SetGuideLine();
//}
//
//void BettleManager::Update() {
//
//}
//



// -> 생성자로 넣어야 할듯?
void BettleManager::SetTarget(Player* nowPlayer, Enemy* nowEnemy) {
	m_Player = nowPlayer;
	m_Enemy = nowEnemy;
}


//Scene에서 deltaTime 설정 -> 임시 -> 없어도 됨!!
void BettleManager::SetDeltaTime(float deltaTime) { 
	m_DeltaTime = deltaTime; 
	m_Player->SetDeltaTime(deltaTime);
	m_Enemy->SetDeltaTime(deltaTime);
}



bool BettleManager::ComparePatten( std::vector<int> InputNode){		  //현재 마우스의 입력 받기  -> 승규님 데이터 받기
	std::vector<int> playerPatten = m_Player->GetNowPatten();
	std::vector<int> EnemyPatten = m_Enemy->GetNowPatten();
	bool isPlayerAttack = false;
	bool isEnemyAttack = false;
	bool isPlayerGuard = false;
	
	if (m_Player->isPlayingPatten) {
		//아군 가이드라인1 체크
		for (int i = 0; i < InputNode.size(); i++) {
			if (playerPatten[i] != InputNode[i]) break;
			isPlayerAttack == true;
		}
		//아군 가이드라인2 체크
		for (int i = 0; i < InputNode.size(); i++) {
			if (playerPatten[i + 9] != InputNode[i]) break;
			isPlayerAttack == true;
		}

		// 플레이어 , 적 상태 변경 + 공방계산
		if (isPlayerAttack == true) {
			// 나중에 구현하기!!!
			//플레이어 State Attack, 적 State hit
			m_Player->SetState("Player_AttackSuccess");
			if(m_Enemy->GetDefenseRate() >=  RandomReturn(100))
				m_Enemy->SetState(); // 방어
			                         
			else {
				m_Enemy->SetState(); // 피격됨
				m_Enemy->GetDamage(m_Player->GetAttack());
			}
			m_Enemy->GetSpiritdamage(m_Player->GetSpiritAttack());
			m_Player->isPlayingPatten = false;
		}
	}
	
	if (m_Enemy->isPlayingPatten) {
		// 패링 계산용 퍼센트 계산
		

		//적군 공격 패턴 체크
		for (int i = 0; i < InputNode.size(); i++) {
			if (EnemyPatten[i] != InputNode[InputNode.size() - 1 - i]) {  // 방어는 역순!!
				isPlayerGuard = true;
				break;
			}
			isEnemyAttack == true;

		}

		//
		if (isPlayerGuard) {				// 막음
			m_Player->SetState("Player_Guard");			// 가드
			if (m_Enemy->GetAttackTimePercent() >= 75) {
				m_Enemy->SetState("Player_Perry");		//패링
			}
		}
		if(isEnemyAttack){
			//플레이어 State hit, 적 State Attack 
			m_Enemy->SetState(); // 공격
			if (m_Player->GetDefenseRate() >= RandomReturn(100)) {
				m_Player->SetState("Player_Defence"); // 방어
			}
			else {
				m_Player->SetState("Player_Hit");    // 피격됨
				m_Player->GetDamage(m_Enemy->GetAttack());
			}
			m_Player->GetSpiritdamage(m_Player->GetSpiritAttack());
			m_Enemy->isPlayingPatten = false;
		}
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

void BettleManager::CalStat(){

}

//상중하 판별 용도, 추가되면 가이드라인 추가에 넣어주기
enum AttackPosition { Up, Middle, Low, NonePos };
AttackPosition ConvertEndNodeToPosition(int endNode, int Damage) {
	int tmpDanamge = 0;
	switch (endNode)
	{
	case 1:  return Up;
	case 2:  return Up;
	case 3:  return Up;
	case 4:  return Middle;
	case 5:  return Middle;
	case 6:  return Middle;
	case 7:  return Low;
	case 8:  return Low;
	case 9:  return Low;
	default: return NonePos;
	}
}