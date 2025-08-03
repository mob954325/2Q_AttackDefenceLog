#include "BettleManager.h"
#include "../LiveObject/Player.h"
#include "../LiveObject/Enemy.h"
#include "../LiveObject/LiveObject.h"


void BettleManager::OnStart() {
	SetGuideLine();
}

void BettleManager::Update() {

}

void BettleManager::EndBettle() {

}


// -> 생성자로 넣어야 할듯?
void BettleManager::SetTarget(Player* nowPlayer, Enemy* nowEnemy) {
	m_Player = nowPlayer;
	m_Enemy = nowEnemy;
}


std::vector<int> BettleManager::SetGuideLine(LiveObject* unknown ){  //쿨타임 확인 후, 가이드라인, 적 공격 라인 생성
	if (typeid(unknown) == typeid(Player*)) {
		if (m_Player->isZeroCool) { return m_Player->GetNowPatten();}
	}
	
	if (typeid(unknown) == typeid(Enemy*)) {
		if (m_Enemy->isZeroCool) { return m_Enemy->GetNowPatten(); }
	}
}

//Scene에서 deltaTime 설정 -> 임시
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
	for (int i = 0; i < InputNode.size(); i++) {
		if (playerPatten[i] != InputNode[i]) break;
		isPlayerAttack == true;
	}

	for (int i = 0; i < InputNode.size(); i++) {
		if (playerPatten[i+9] != InputNode[i]) break;
		isPlayerAttack == true;
	}

	for (int i = 0; i < InputNode.size(); i++) {
		if (EnemyPatten[i] != InputNode[i]) break;
		isEnemyAttack == true;
	}
}

void BettleManager::DeciedBettelState(){ //마우스 데이터를 비교해서 현재 상태 결정하기
}

void BettleManager::CalStat(){

}

