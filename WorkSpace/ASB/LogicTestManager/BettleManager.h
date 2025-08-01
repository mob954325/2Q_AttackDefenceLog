#pragma once
#include "../LiveObject/Player.h"
#include "../LiveObject/Enemy.h"

class State;

//역할 : 전체 전투 담당
class BettleManager {
public:
	BettleManager() {};
	~BettleManager() {};

	void OnstartBettle();
	void Update();
	void EndBettle();

private:
	Player* player;
	Enemy* Enemy;

	void SelectPatten();  //각 객체가 사용할 패턴을 고름
	void CalCooTime();    //각 객체의 쿨타임을 확인
	void SetGuideLine();  //쿨타임 확인 후, 가이드라인, 적 공격 라인 생성
	void GetPatten();     //현재 마우스의 입력 받기  -> 승규님 데이터 받기

public:
};

// 역할 : 생성 파괴 담당
class LiveObjectManager {
	LiveObjectManager() {};
};

// 역할 state 결정 담당
class DecideState {

};


// 역할 :  각 오브젝트의 스탯 변화 담당
class StatManager {

};

