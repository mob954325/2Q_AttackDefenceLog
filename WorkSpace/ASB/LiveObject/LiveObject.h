#pragma once
#include <iostream>
#include <string>
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/AnimationRenderer.h"
#include "Components/Logic/InputSystem.h"
#include "components/Collision/AABBCollider.h"
#include "Components/Physics/Rigidbody2D.h"
#include "../Component/StateController.h"
#include "../LogicTestManager/AttackPatternManager.h"
#include <queue>

// 주의!!! 씬 단위로 델타타임을 고정시킬 예정이라서 씬의 업데이트 처음에 무조건 시간 받아오기!!!!

/*2025.07.28 - 안성빈
 플레이어나  적들이 상속받을 기본적인 오브젝트
 들어가는 변수 : ID, 이름 , 체력, 공격력, 기세공격력, 회피율, 방어율
 들어가는 함수 : 위의 변수를 가져오는 함수, 설정하는 함수  
			     + 부모에 없는 자식의 맴버를 가져오는 함수
*/

/*25.08.01 - 안성빈
	배틀 매니저에서 함수만 호출하여 사용할 수 있도록 함수 분할중
	지금은 기능에 따라 다 분해하고 있지만 이후에 같이 실행되는 것은 함수를 병합할 예정
	-> 기능을 따로 정리하고 눈에 안들어오는 상태로 구현할려고하니까 머리가 안돌아감 ㅡ.ㅡ
*/


class LiveObject : public MonoBehavior
{
public:
	LiveObject() {};
	virtual ~LiveObject() {};



public:
	// 값 가져오는 함수들
	std::string GetID() { return Object_ID; }		                // ID 반환
	std::wstring GetName() { return Object_Name; }				    // 이름 반환
	float GetHp() { return Object_Hp; }							    // 체력 반환
	float GetAttack() { return Object_Attack; }						// 공격력 반환
	float GetSpiritAttack() { return Object_SpiritAttack; }		// 기세 공격력 반환
	float GetDefenseRate() { return Object_DefenseRate; }			// 방어율 반환
	float GetPlayingAttackTime() const {return Object_PlayingAttackTime;}  //가이드라인이 떠있는 시간
	float GetNowPlayingAttackTime() const {return Object_nowPlayingAttackTime;} //현채 가이드라인이 뜬 기간
	float GetSpiritAmount() { return Object_SpiritAmount; }
	
	// 설정 함수들
	void SetID(const std::string& id) { Object_ID = id; }							 // ID 설정
	void SetName(const std::wstring& name) { Object_Name = name; }					 // 이름 설정
	void SetHp(float hp) { Object_Hp = hp; }									     // 체력 설정
	void SetAttack(float attack) { Object_Attack = attack; }						 // 공격력 설정
	void SetSpiritAttack(float SpiritAttack) { Object_SpiritAttack = SpiritAttack; } // 기세 공격력 설정
	void SetDefenseRate(float defenseRate) { Object_DefenseRate = defenseRate; }     // 방어율 설정
	void SetPlayingAttackTime(float time) {Object_PlayingAttackTime = time;}		 // 가이드라인이 떠있는 시간 설정
	


	//값 변경 함수
	void GetDamage(float damageAmount) {Object_Hp -= damageAmount;}
	void GetSpiritdamage(float SpiritdamageAmount) { Object_SpiritAmount -= SpiritdamageAmount; }
	void RestoreSpiritDamage(float SpiritRestoreAmount) { Object_SpiritAmount += SpiritRestoreAmount; }
	

	//각 객체의 업데이트에 들어갈 함수
	//virtual void SetDeltaTime(float deltaTime) = 0; //씬 단위로 델타타임을 통일!!!! -> 시간을 받아야함
	virtual void SetCoolTime() = 0;    //각 객체의 쿨타임이 0이 되었을 때, 다음 쿨타임을 설정함
	virtual void CalSpiritTime() = 0;  //이거는 플레이어 : -0.3,  적 : +0.3  고정!!!

	//배틀 매니저에 들어갈 스탯 계산할 함수
	virtual void SelectPatten() = 0;   //각 객체가 사용할 패턴을 고름
	virtual void SetNowPatten() = 0;   //각 객체가 현재 패턴을 반환함
	virtual void AddPattenLoop() = 0;  // 각 플래그를 관리하여 패턴을 추가하는 코드
	

	//state에 관련된 함수
	virtual void SetState(std::string setStateName) = 0;
	virtual void OnCreateState() = 0;



protected: 
	std::string Object_ID; 	      // ID
	std::wstring Object_Name;     // 이름
	float Object_Hp;		      // 체력
	float Object_Attack;		  // 공격력
	float Object_SpiritAttack;	  // 기세 공격력
	float Object_DefenseRate;	  // 방어율

	float Object_SpiritAmount;    // 전체 기세
	float Object_NowSpiritAmount; // 현재 기세 
	float Object_OverTimeSpirit;  // 기세 감소 시간을 저장할 변수 

	float Object_CoolTime;		  // 공격 대기시간
	float Object_nowCoolTime;	  // 현재 대기시간

	float Object_PlayingAttackTime; //패턴의 입력 대기 시간
	float Object_nowPlayingAttackTime; //현재 패턴의 입력 대기 시간


	AttackPatternManager m_PattenManager; // 패턴 매니저를  참조로 받아  사용할 변수
	

	float NodeTime;				  // 가이드라인의 판정 시간
	




	
public:
	//배틀 매니저에서 사용할 flag
	bool isPattenCooldown = false; //공격 패턴의 쿨타임이 줄어드는지
	bool isAddPath = false;        // 패턴 추가 했는지
};

