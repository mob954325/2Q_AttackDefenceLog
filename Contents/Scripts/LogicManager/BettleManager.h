#pragma once
#include "../LiveObject/Player.h"
#include "../LiveObject/Enemy.h"
#include "AttackPatternManager.h"
#include "../Engine/Utils/EventDelegate.h"
#include "Scripts/Slider/GiseGauge.h"
class State;

enum GroggyState { playerGroggy = 0, enemyGroggy, noneGroggy };

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
	void OnStart();
	void OnDestroy() {};
	void OnUpdate();
	void OnFixedUpdate() {};




	//-----------------------------------------------------------------------------------------------

public:
	//상중하에 따라서 체력과 기세 데미지를 적용함, 플레이어와 적 동일하게 적용
	//상중하에 따라서 체력 데미지 리턴하는 함수
	//   - 필요시 분리 가능!!
	float ConvertHPDamageToPos(AttackPosition lastPos, float HpDamage) {
		switch (lastPos)
		{
		case UpNode:      return  HpDamage * 1.25f;    // 상단 노드일때 1.25배 추가뎀
		case MiddleNode:  return  HpDamage;            // 중단 노드
		case LowNode:     return  HpDamage * 0.75f;    // 하단 노드
		default:		  return  0.0f;
		}
	}

	//상중하에 따라서  기세 데미지 리턴하는 함수
	float ConvertSpiritDamageToPos(AttackPosition lastPos, float SpiritDamage) {
		switch (lastPos)
		{
		case UpNode:      return SpiritDamage * 0.75f;  // 상단 노드일때  0.75배 뎀감
		case MiddleNode:  return SpiritDamage;			// 중단 노드
		case LowNode:     return SpiritDamage * 1.25f;  // 하단 노드
		default:		  return 0.0f;
		}
	}


private:

	//플레이어의 기세 게이지가 0 일때, 적이 플레이어에게 데미지를 주는 배율
	float spiritDamageMulToPlayer = 2.5f;

	//------------------------------------------------------------------------------------------------


public:
	Player* m_Player = nullptr;
	Enemy* m_Enemy = nullptr;

	EventDelegate<int> onParry; // 밖에 int << 마지막노드
	EventDelegate<int> onGuard;

private:

	AttackPatternManager* m_PattenManager;
	float m_DeltaTime = 0.0f;


	/// 업데이트에 들어갈 함수들
	std::vector<int> SetGuideLine(LiveObject* unknown);     //쿨타임 확인 후, 가이드라인, 적 공격 라인 생성

	void SetStateFormPattern();	  //현재 마우스의 입력 받기  -> 승규님 데이터 받기
	void ResetState();
	void SetGroggyState();


	//float ConvertHPDamageToPos(AttackPosition lastPos, float HpDamage);
	//float ConvertSpiritDamageToPos(AttackPosition lastPos, float SpiritDamage);


public:
	void SetInputNode(std::vector<int> InputNode);  // 현재 노드의 입력 넣기
	//Scene의 Start에 들어갈 것들
	void SetForStart(AttackPatternManager* pattenManager); //-> 이거는 생성자에 넣을수도?
	void ChangeFinalState();
	void SetSpiritGauge();  // 기세 게이지  세팅하는 함수
	std::vector<int> nowNode;
	int RandomReturn(int MaxInt);
	void FinalAttackToEnemy(); // 홀드 어택 !!!!!!
	

private:
	GiseGauge* giseObj{};
	float ChangeValue = 0.0f;
	float TotalValue = 0.0f;
	float preSpiritAmount = 0.0f;
	float allDistancePercent = 0.0f;
	GroggyState nowManagerState = noneGroggy;
	GroggyState preManagerState = noneGroggy;
};









