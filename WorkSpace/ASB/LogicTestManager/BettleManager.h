#pragma once
#include "../LiveObject/Player.h"
#include "../LiveObject/Enemy.h"
#include "AttackPatternManager.h"
class State;


//
/*
  역할 : 전체 전투 담당 매니저
  주의 : 씬 전체의 시간을 통일 할 예정!!!!
*/
class BettleManager : public MonoBehavior {
public:
	BettleManager() {};
	~BettleManager() {};

	void OnCreate() {};
	void OnStart() ;
	void OnDestroy() {};
	void OnUpdate() ;
	void OnFixedUpdate() {};
	Player* m_Player = nullptr;
	Enemy* m_Enemy = nullptr;
private:
	
	AttackPatternManager* m_PattenManager;
	float m_DeltaTime = 0.0f;


	/// 업데이트에 들어갈 함수들
	std::vector<int> SetGuideLine(LiveObject* unknown);     //쿨타임 확인 후, 가이드라인, 적 공격 라인 생성
	
	void SetStateFormPattern();	  //현재 마우스의 입력 받기  -> 승규님 데이터 받기
	void DeciedBettelState(); //마우스 데이터를 비교해서 현재 상태 결정하기
	void PrecticeNode();
public:
	void SetInputNode(std::vector<int> InputNode);  // 현재 노드의 입력 넣기
	//Scene의 Start에 들어갈 것들
	void SetForStart(AttackPatternManager* pattenManager); //-> 이거는 생성자에 넣을수도?
	void ChangeFinalState();
	void SetDeltaTime(float deltaTime);			        //Scene에서 deltaTime 설정
	std::vector<int> nowNode;
	int RandomReturn(int MaxInt);

};








