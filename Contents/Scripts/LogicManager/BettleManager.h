#pragma once
#include "../LiveObject/Player.h"
#include "../LiveObject/Enemy.h"
#include "AttackPatternManager.h"
#include "../Engine/Utils/EventDelegate.h"
#include "Scripts/Slider/GiseGauge.h"
#include "Scripts/HPBar/HpGauge.h"
class State;

enum GroggyState 
{
	playerGroggy = 0,
	enemyGroggy,
	noneGroggy 
};

//
/*
  역할 : 플레이어와 적 전투 담당 매니저
  주의 : 씬 전체의 시간을 통일 할 예정!!!!
*/
class BettleManager : public MonoBehavior {
public:
	BettleManager() {};
	~BettleManager() {};

	void OnCreate() override;
	void OnStart();
	void OnUpdate();

	/// <summary>
	/// PatternControlObject가 호출할 체력 게이지 초기화 함수
	/// </summary>
	void InitHpGauge();

public:
	//상중하에 따라서 체력과 기세 데미지를 적용함, 플레이어와 적 ㄴ동일하게 적용
	//상중하에 따라서 체력 데미지 리턴하는 함수
	//   - 필요시 분리 가능!!
	float ConvertHPDamageToPos(AttackPosition lastPos, float HpDamage);

	//상중하에 따라서  기세 데미지 리턴하는 함수
	float ConvertSpiritDamageToPos(AttackPosition lastPos, float SpiritDamage);

private:
	//플레이어의 기세 게이지가 0 일때, 적이 플레이어에게 데미지를 주는 배율
	float spiritDamageMulToPlayer = 2.5f;

	Vector2 Player2{ 400.0f , 200.0f }; // ???
	Vector2 Enemy2{ 800.0f , 200.0f };
    
public:
	Player* m_Player = nullptr;
	Enemy* m_Enemy = nullptr;

	EventDelegate<int> onParry;		// 패링 이벤트 - 밖에 int << 마지막노드
	EventDelegate<int> onGuard;		// 회피 이벤트

	EventDelegate<> onStartBlow;    // 한붓그리기 시작 이벤트
	bool usedStartBlow = false;		// 델리게이트 한번만 호출할려는 플래그임

	EventDelegate<> onFinalBlow;	// 연격 이벤트
	EventDelegate<>	onTimeout;		// 패턴 종료 이벤트

private:

	AttackPatternManager* m_PattenManager;
	float m_DeltaTime = 0.0f;


	/// 업데이트에 들어갈 함수들
	std::vector<int> SetGuideLine(LiveObject* unknown);     //쿨타임 확인 후, 가이드라인, 적 공격 라인 생성

	/// <summary>
	/// 들어온 입력 노드에 따라서 공격, 방어를 처리하는 함수
	/// </summary>
	void SetStateFormPattern();	  //현재 마우스의 입력 받기  -> 승규님 데이터 받기

	/// <summary>
	/// (preManagerState != nowManagerState && preManagerState == enemyGroggy) 일 때 처리하는 update 함수 - 함수 이름의 의미를 모르겠음 
	/// </summary>
	void ResetState();

	/// <summary>
	/// 각 그로기 상태에 따라 nowManagerState 변수 값을 해당 그로기 상태로 변경하는 함수
	/// </summary>
	void SetGroggyState();


public:
	/// <summary>
	/// 현재 노드의 입력 넣기 - Pattern Manager에서 사용
	/// </summary>
	/// <param name="InputNode">받을 노드 인덱스들</param>
	void SetInputNode(std::vector<int> InputNode); 

	void SetStateFormPatternPlayerGroggy();
	void SetStateFormPatternEnemyGroggy();
	void SetStateFormPatternIdle();



	void  ChangeFinalStateIdle();
	void  ChangeFinalStateEnemyGroggy();
	void  ChangeFinalStatePlayerGroggy();
	void ChangeCommonFinalState();

	void SetAnimationAtOtherGroggy(); // 연격 후에 애니매이션 출력
	float AniTime = 0.0f;             // 애니메이션 출력 시간


	//Scene의 Start에 들어갈 것들

	/// <summary>
	/// 플레이어와 적의 상태에 따라 그로기와 사망 상태로 변경하는 함수
	/// </summary>
	void ChangeFinalState();

	/// <summary>
	/// 기세 게이지  세팅하는 함수
	/// </summary>
	void SetSpiritGauge();		

	/// <summary>
	/// 현재 확인하는 노드 내용 ( 패턴 index 값 )
	/// </summary>
	std::vector<int> nowNode;	

	/// <summary>
	/// 적에게 홀드 어택을 실행하는 함수
	/// </summary>
	void FinalAttackToEnemy(); // 홀드 어택 !!!!!!
	

private:
	HpGauge* HpObj{};
	GiseGauge* giseObj{};
	float giseChangeValue = 0.0f;				// 변경될 기세 값
	float giseTotalValue = 0.0f;				// 최종 기세 값
	float preSpiritAmount = 0.0f;				// 이전 기세 게이지량
	float allDistancePercent = 0.0f;			// 연격 길이 퍼센트 값
	GroggyState nowManagerState = noneGroggy;	// 매니저의 그로기 상태 여부
	GroggyState preManagerState = noneGroggy;	// 매니저의 이전 그로기 상태 여부

	bool isOncePatternAttack = false; // 한붓그리기 공격 끝나는 bool 값

	bool isEffectOnce = true;

	std::vector<int> tmpAttackNode;             // 플레이어가 연격 후 임시 저장 할 int 벡터
	bool isPlayingAni = false; // 연격이 끝나고 sprite가 나오는 시간인지?
};









